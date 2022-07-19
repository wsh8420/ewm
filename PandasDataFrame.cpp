//
// Created by watson on 22-7-18.
//
#include "PandasDataFrame.h"
#include "string.h"
#include "iostream"
#include "math.h"

const double EPS = 1e-6;//1的负6次方
const double DOUBLE_MAX = 1.79769e+308;
const double DOUBLE_MIN = 1.79769e-308;


using namespace std;

PandasDataFrame::PandasDataFrame() {
}

inline int get_size(int index, int span, int min_periods) {
    int size = 0;
    if (index >= span) {
        size = span;
    }

    if (index < span && index >= min_periods) {
        size = index;
    }
    return size;
}

inline double get_alpha(int index, int span, int min_periods) {
//    int size = get_size(index, span, min_periods);
    return 2 / (span + 1.0);
}

static double get_ewm_mean(double *data, double alpha, int idx) {
    if (idx > 1) {
        return (1 - alpha) * get_ewm_mean(data, alpha, idx - 1) + alpha * data[idx - 1];
    } else {
        return data[0];
    }
}

double PandasDataFrame::ewm_mean(double *data, int index, int span, int min_periods, double pre_ewm_val) {
    if (data == nullptr || index <= 0 || span <= 0 || index < min_periods)
        return -1;

    double alpha = get_alpha(index, span, min_periods);
    return alpha * data[index - 1] + (1 - alpha) * pre_ewm_val;
}

inline double *fill_buckets(double *data, int index, int span) {
    double *filled_data = new double[span];
    memset(filled_data, 0, span);
    int filled_len = span - index;
    memcpy(filled_data + filled_len, data, index * sizeof(double));
    for (int i = 0; i < filled_len; i++) {
        filled_data[i] = data[0];
    }
    return filled_data;
}

double PandasDataFrame::ewm_mean(double *data, int index, int span, int min_periods) {
    if (data == nullptr || index <= 0 || span <= 0 || index < min_periods)
        return -1;

    double alpha = get_alpha(index, span, min_periods);
    if (index < span) {
        double *filled_data = nullptr;
        filled_data = fill_buckets(data, index, span);
        if (filled_data != nullptr) {
            double ret = get_ewm_mean(filled_data, alpha, span);
            delete[] filled_data;
            filled_data = nullptr;
            return ret;
        }
    }

    return get_ewm_mean(data, alpha, index);
}

double PandasDataFrame::rolling_mean(double *data, int index, int rolllen, int min_periods) {
    if (data == nullptr || index <= 0 || rolllen <= 0 || index < min_periods)
        return -1;

    auto size = get_size(index, rolllen, min_periods);
    double sum = 0;
    for (int i = index - size; i < index; ++i) {
        sum += data[i];
    }
    return sum / size;
}

double PandasDataFrame::rolling_max(double *data, int index, int rolllen, int min_periods) {
    if (data == nullptr || index <= 0 || rolllen <= 0 || index < min_periods)
        return -1;

    auto size = get_size(index, rolllen, min_periods);
    double max_val = DOUBLE_MIN;
    for (int i = index - size; i < index; ++i) {
        if (max_val + EPS < data[i])
            max_val = data[i];
    }
    return max_val;
}

double PandasDataFrame::rolling_min(double *data, int index, int rolllen, int min_periods) {
    if (data == nullptr || index <= 0 || rolllen <= 0 || index < min_periods)
        return -1;

    int size = get_size(index, rolllen, min_periods);
    double min_val = DOUBLE_MAX;
    for (int i = index - size; i < index; ++i) {
        if (data[i] + EPS < min_val)
            min_val = data[i];
    }
    return min_val;
}

inline double average(double *x, int len) {
    double sum = 0;
    for (int i = 0; i < len; i++) // 求和
        sum += x[i];
    return sum / len; // 得到平均值
}

inline double variance(double *x, int len) {
    double sum = 0;
    double avg = average(x, len);
    for (int i = 0; i < len; i++) // 求和
        sum += pow(x[i] - avg, 2);
    return sum / len; // 得到方差
}

inline double standardDev(double *x, int len) {
    double var = variance(x, len);
    return sqrt(var); // 得到标准差
}

double PandasDataFrame::rolling_std(double *data, int index, int rolllen, int min_periods) {
    if (data == nullptr || index <= 0 || rolllen <= 0 || index < min_periods)
        return -1;

    int size = get_size(index, rolllen, min_periods);
    return standardDev(data + index - size, size);
}

double *PandasDataFrame::sz_rolling_mean(double *data, int index, int rolllen, int min_periods) {
    if (data == nullptr || index <= 0 || rolllen <= 0 || index < min_periods)
        return nullptr;

    double *arr_roll = new double[index];
    memset(arr_roll, 0, index);
    for (int i = 0; i < index; i++) {
        if (i == 0) {
            arr_roll[0] = data[0];
        } else {
            arr_roll[i] = rolling_mean(data, i + 1, rolllen, min_periods);
        }
    }

    return arr_roll;
}

double *PandasDataFrame::sz_rolling_max(double *data, int index, int rolllen, int min_periods) {
    if (data == nullptr || index <= 0 || rolllen <= 0 || index < min_periods)
        return nullptr;

    double *arr_roll = new double[index];
    memset(arr_roll, 0, index);
    for (int i = 0; i < index; i++) {
        if (i == 0) {
            arr_roll[0] = data[0];
        } else {
            arr_roll[i] = rolling_max(data, i + 1, rolllen, min_periods);
        }
    }

    return arr_roll;
}

double *PandasDataFrame::sz_rolling_min(double *data, int index, int rolllen, int min_periods) {
    if (data == nullptr || index <= 0 || rolllen <= 0 || index < min_periods)
        return nullptr;

    double *arr_roll = new double[index];
    memset(arr_roll, 0, index);
    for (int i = 0; i < index; i++) {
        if (i == 0) {
            arr_roll[0] = data[0];
        } else {
            arr_roll[i] = rolling_min(data, i + 1, rolllen, min_periods);
        }
    }

    return arr_roll;
}

double *PandasDataFrame::sz_rolling_std(double *data, int index, int rolllen, int min_periods) {
    if (data == nullptr || index <= 0 || rolllen <= 0 || index < min_periods)
        return nullptr;

    double *arr_roll = new double[index];
    memset(arr_roll, 0, index);
    for (int i = 0; i < index; i++) {
        arr_roll[i] = rolling_std(data, i + 1, rolllen, min_periods);
    }

    return arr_roll;
}
