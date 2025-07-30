#ifndef LIGHTGBM_SYSTEM_LIGHTGBMWRAPPER_H
#define LIGHTGBM_SYSTEM_LIGHTGBMWRAPPER_H
#include <vector>
#include <string>

class LightGBMWrapper {
public:
    LightGBMWrapper() = default;

    bool train(const std::vector<double>& data,
               const std::vector<float>& labels,
               int32_t nrow, int32_t ncol,
               const std::string& model_file = "model.txt");

    bool predict(const std::vector<double>& features, int32_t ncol,
                 const std::string& model_file = "model.txt");
};

#endif //LIGHTGBM_SYSTEM_LIGHTGBMWRAPPER_H