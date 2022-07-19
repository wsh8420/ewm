//
// Created by watson on 22-7-18.
//
#ifndef EWM_PANDASDATAFRAME_H
#define EWM_PANDASDATAFRAME_H

class PandasDataFrame {
public:
    PandasDataFrame();

public:
    /**
     * @brief 根据上一次计算的ewm计算最新的指数移动平均值
     *
     * @param data           待计算值
     * @param index          有效的数组长度
     * @param span           计算平均值的移动窗口长度
     * @param min_periods    最小移动步长，最小移动步长与窗口长度是配合使用的，当输入的数组长度 >=最小移动步长，
     * 且小于 窗口长度，则计算的窗口长度=数组长度；当输入的数组长度  < 最小移动步长，则结果为Nan；
     * 当输入的数组长度 >=窗口长度，则计算的窗口长度=窗口长度
     *
     * @return               返回最新的ewm,如果<0表示为计算异常
     */
    double ewm_mean(double *data, int index, int span, int min_periods, double pre_ewm_val);

    /**
     * @brief 从头开始计算最新的指数移动平均值
     *
     * @param data           待计算值
     * @param index          有效的数组长度
     * @param span           计算平均值的移动窗口长度
     * @param min_periods    最小移动步长，最小移动步长与窗口长度是配合使用的，当输入的数组长度 >=最小移动步长，
     * 且小于 窗口长度，则计算的窗口长度=数组长度；当输入的数组长度  < 最小移动步长，则结果为Nan；
     * 当输入的数组长度 >=窗口长度，则计算的窗口长度=窗口长度
     *
     * @return               返回最新的指数移动平均值,如果<0表示为计算异常
     */
    double ewm_mean(double *data, int index, int span, int min_periods);

    /**
     * @brief 求平均值
     *
     * @param data           待计算值
     * @param index          有效的数组长度
     * @param rolllen        计算平均值的移动窗口长度
     * @param min_periods    计算平均值的最小步长
     *
     * @return               返回N个数的平均值,如果<0表示为计算异常
     */
    double rolling_mean(double *data, int index, int rolllen, int min_periods);

    /**
     * @brief 求最大值
     *
     * @param data           待计算值
     * @param index          有效的数组长度
     * @param rolllen        计算最大值的移动窗口长度
     * @param min_periods    计算最大值的最小步长
     *
     * @return               返回N个数的最大值,如果<0表示为计算异常
     */
    double rolling_max(double *data, int index, int rolllen, int min_periods);

    /**
     * @brief 求最小值
     *
     * @param data           待计算值
     * @param index          有效的数组长度
     * @param rolllen        计算最小值的移动窗口长度
     * @param min_periods    计算最小值的最小步长
     *
     * @return               返回N个数的平均值,如果<0表示为计算异常
     */
    double rolling_min(double *data, int index, int rolllen, int min_periods);

    /**
     * @brief 得到标准差值
     *
     * @param data           待计算值
     * @param index          有效的数组长度
     * @param rolllen        计算均方差的移动窗口长度
     * @param min_periods    计算均方差的最小步长
     *
     * @return               返回N个数的均方差值,如果<0表示为计算异常
     */
    double rolling_std(double *data, int index, int rolllen, int min_periods);

    /**
     * @brief 求平均值，注意不要忘了释放返回数组内存
     *
     * @param data           待计算值
     * @param index          有效的数组长度
     * @param rolllen        计算平均值的移动窗口长度
     * @param min_periods    计算平均值的最小步长
     *
     * @return               返回N个数的平均值,如果<0表示为计算异常
     */
    double* sz_rolling_mean(double *data, int index, int rolllen, int min_periods);

    /**
     * @brief 求最大值，注意不要忘了释放返回数组内存
     *
     * @param data           待计算值
     * @param index          有效的数组长度
     * @param rolllen        计算最大值的移动窗口长度
     * @param min_periods    计算最大值的最小步长
     *
     * @return               返回N个数的最大值,如果<0表示为计算异常
     */
    double* sz_rolling_max(double *data, int index, int rolllen, int min_periods);

    /**
     * @brief 求最小值，注意不要忘了释放返回数组内存
     *
     * @param data           待计算值
     * @param index          有效的数组长度
     * @param rolllen        计算最小值的移动窗口长度
     * @param min_periods    计算最小值的最小步长
     *
     * @return               返回N个数的平均值,如果<0表示为计算异常
     */
    double* sz_rolling_min(double *data, int index, int rolllen, int min_periods);

    /**
     * @brief 得到标准差值，注意不要忘了释放返回数组内存
     *
     * @param data           待计算值
     * @param index          有效的数组长度
     * @param rolllen        计算均方差的移动窗口长度
     * @param min_periods    计算均方差的最小步长
     *
     * @return               返回N个数的均方差值,如果<0表示为计算异常
     */
    double* sz_rolling_std(double *data, int index, int rolllen, int min_periods);
};

#endif //EWM_PANDASDATAFRAME_H
