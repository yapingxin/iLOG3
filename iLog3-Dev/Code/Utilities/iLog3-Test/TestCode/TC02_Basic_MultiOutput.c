#include "TC02_Basic_MultiOutput.h"

#include "LOGS.h"

#define LOG_STYLES_DOG        ( LOG_STYLE_DATETIMEMS | LOG_STYLE_LOGLEVEL | LOG_STYLE_PID | LOG_STYLE_TID | LOG_STYLE_SOURCE | LOG_STYLE_FORMAT | LOG_STYLE_NEWLINE )
#define LOG_STYLES_EVENT      ( LOG_STYLE_DATETIMEMS | LOG_STYLE_CUSTLABEL1 | LOG_STYLE_FORMAT | LOG_STYLE_NEWLINE )

int TC02_Basic_MultiOutput()
{
    LOGS		*gs = NULL;
    LOG		*g = NULL;
    char		buffer[64 + 1] = "";
    long		buflen = sizeof(buffer) - 1;

    /* 创建日志句柄集合 */
    gs = CreateLogsHandleG(); /* 带后缀G的函数创建的日志句柄集合自动设置成线程安全的全局缺省日志句柄集合 */
    if (gs == NULL)
    {
        printf("创建日志句柄集合失败errno[%d]\n", errno);
        return -1;
    }
    else
    {
        printf("创建日志句柄集合成功\n");
    }

    /* 创建日志句柄 */
    g = CreateLogHandle();
    if (g == NULL)
    {
        printf("创建日志句柄失败errno[%d]\n", errno);
        return -1;
    }
    else
    {
        printf("创建日志句柄成功\n");
    }
    /* 设置日志输出文件名 */
    SetLogOutput(g, LOG_OUTPUT_FILE, "test_LOGS.log", LOG_NO_OUTPUTFUNC);
    /* 设置当前日志过滤等级 */
    SetLogLevel(g, LOG_LEVEL_INFO);
    /* 设置当前行日志风格方案 */
    SetLogStyles(g, LOG_STYLES_DOG, LOG_NO_STYLEFUNC);
    /* 刚刚创建的日志句柄加到日志句柄集合中 */
    AddLogToLogs(gs, "file", g);

    /* 创建日志句柄 */
    g = CreateLogHandle();
    if (g == NULL)
    {
        printf("创建日志句柄失败errno[%d]\n", errno);
        return -1;
    }
    else
    {
        printf("创建日志句柄成功\n");
    }
    /* 设置日志输出文件名 */
    SetLogOutput(g, LOG_OUTPUT_STDOUT, NULL, LOG_NO_OUTPUTFUNC);
    /* 设置当前日志过滤等级 */
    SetLogLevel(g, LOG_LEVEL_ERROR);
    /* 设置线程私有标签 */
    SetLogCustLabel(g, 1, "COREIB1");
    /* 设置当前行日志风格方案 */
    SetLogStyles(g, LOG_STYLES_EVENT, LOG_NO_STYLEFUNC);
    /* 刚刚创建的日志句柄加到日志句柄集合中 */
    AddLogToLogs(gs, "stdout", g);

    /* 以不同日志等级写行日志集合 */
    DEBUGLOGSG("hello DEBUG"); /* 这行日志因等级不够，被华丽的过滤了 */
    INFOLOGSG("hello INFO");
    WARNLOGSG("hello WARN");
    ERRORLOGSG("hello ERROR");
    FATALLOGSG("hello FATAL");

    /* 以不同日志等级写十六进制块日志集合 */
    DEBUGHEXLOGSG(buffer, buflen, "hello DEBUG buffer[%ld]", buflen); /* 又一个被华丽的过滤 */
    INFOHEXLOGSG(buffer, buflen, "hello INFO buffer[%ld]", buflen);
    WARNHEXLOGSG(buffer, buflen, "hello WARN buffer[%ld]", buflen);
    ERRORHEXLOGSG(buffer, buflen, "hello ERROR buffer[%ld]", buflen);
    FATALHEXLOGSG(buffer, buflen, "hello FATAL buffer[%ld]", buflen);

    /* 销毁日志句柄集合 */
    DestroyLogsHandleG(); /* 日志句柄集合内包含的两个日志句柄连带销毁掉 */
    printf("释放日志句柄集合\n");

    return 0;
}
