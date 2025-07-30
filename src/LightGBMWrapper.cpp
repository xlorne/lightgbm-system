#include "LightGBMWrapper.h"

#include <filesystem>
#include <LightGBM/c_api.h>
#include <iostream>
#include <fmt/core.h>

bool LightGBMWrapper::train(const std::vector<double>& data,
                            const std::vector<float>& labels,
                            int32_t nrow, int32_t ncol,
                            const std::string& model_file) {
    DatasetHandle dataset;
    BoosterHandle booster;

    if (LGBM_DatasetCreateFromMat(data.data(), C_API_DTYPE_FLOAT64, nrow, ncol, 1,
                                  "max_bin=15", nullptr, &dataset) != 0) {
        fmt::print("❌ 创建 Dataset 失败\n");
        return false;
    }

    LGBM_DatasetSetField(dataset, "label", labels.data(), nrow, C_API_DTYPE_FLOAT32);

    if (LGBM_BoosterCreate(dataset, "objective=binary metric=binary_logloss num_leaves=31", &booster) != 0) {
        fmt::print( "❌ 创建 Booster 失败\n");
        return false;
    }

    for (int i = 0; i < 100; ++i) {
        int is_finished = 0;
        LGBM_BoosterUpdateOneIter(booster, &is_finished);
    }

    if (LGBM_BoosterSaveModel(booster, 0, -1, 0, model_file.c_str()) != 0) {
        fmt::print( "❌ 保存模型失败\n");
        return false;
    }

    LGBM_BoosterFree(booster);
    LGBM_DatasetFree(dataset);

    fmt::print("✅ 模型训练完成，已保存至 {} \n",model_file);
    return true;
}

bool LightGBMWrapper::predict(const std::vector<double>& features, int32_t ncol,
                               const std::string& model_file) {

    if (!std::filesystem::exists(model_file)) {
        fmt::print("❌ 模型文件不存在: {} \n",model_file);
        return false;
    }

    BoosterHandle booster;
    int out_num_iterations;
    int status = LGBM_BoosterCreateFromModelfile(model_file.c_str(), &out_num_iterations, &booster);
    if (status != 0) {
        fmt::print("❌ 加载模型失败，错误码：{}\n", status);
        return false;
    }

    int32_t nrow = 1;
    std::vector<double> result(nrow);
    int64_t out_len;

    if (LGBM_BoosterPredictForMat(
            booster,
            features.data(),
            C_API_DTYPE_FLOAT64,
            nrow,
            ncol,
            1, // row-major
            C_API_PREDICT_NORMAL,
            0,
            -1,
            "",  // 参数
            &out_len,
            result.data()) != 0) {
        fmt::print( "❌ 预测失败\n");
        return false;
    }

    fmt::print("✅ 预测结果: {} \n",result[0]);
    LGBM_BoosterFree(booster);
    return true;
}