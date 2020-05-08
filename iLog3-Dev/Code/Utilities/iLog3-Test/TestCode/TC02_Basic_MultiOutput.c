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

    /* ������־������� */
    gs = CreateLogsHandleG(); /* ����׺G�ĺ�����������־��������Զ����ó��̰߳�ȫ��ȫ��ȱʡ��־������� */
    if (gs == NULL)
    {
        printf("������־�������ʧ��errno[%d]\n", errno);
        return -1;
    }
    else
    {
        printf("������־������ϳɹ�\n");
    }

    /* ������־��� */
    g = CreateLogHandle();
    if (g == NULL)
    {
        printf("������־���ʧ��errno[%d]\n", errno);
        return -1;
    }
    else
    {
        printf("������־����ɹ�\n");
    }
    /* ������־����ļ��� */
    SetLogOutput(g, LOG_OUTPUT_FILE, "test_LOGS.log", LOG_NO_OUTPUTFUNC);
    /* ���õ�ǰ��־���˵ȼ� */
    SetLogLevel(g, LOG_LEVEL_INFO);
    /* ���õ�ǰ����־��񷽰� */
    SetLogStyles(g, LOG_STYLES_DOG, LOG_NO_STYLEFUNC);
    /* �ոմ�������־����ӵ���־��������� */
    AddLogToLogs(gs, "file", g);

    /* ������־��� */
    g = CreateLogHandle();
    if (g == NULL)
    {
        printf("������־���ʧ��errno[%d]\n", errno);
        return -1;
    }
    else
    {
        printf("������־����ɹ�\n");
    }
    /* ������־����ļ��� */
    SetLogOutput(g, LOG_OUTPUT_STDOUT, NULL, LOG_NO_OUTPUTFUNC);
    /* ���õ�ǰ��־���˵ȼ� */
    SetLogLevel(g, LOG_LEVEL_ERROR);
    /* �����߳�˽�б�ǩ */
    SetLogCustLabel(g, 1, "COREIB1");
    /* ���õ�ǰ����־��񷽰� */
    SetLogStyles(g, LOG_STYLES_EVENT, LOG_NO_STYLEFUNC);
    /* �ոմ�������־����ӵ���־��������� */
    AddLogToLogs(gs, "stdout", g);

    /* �Բ�ͬ��־�ȼ�д����־���� */
    DEBUGLOGSG("hello DEBUG"); /* ������־��ȼ��������������Ĺ����� */
    INFOLOGSG("hello INFO");
    WARNLOGSG("hello WARN");
    ERRORLOGSG("hello ERROR");
    FATALLOGSG("hello FATAL");

    /* �Բ�ͬ��־�ȼ�дʮ�����ƿ���־���� */
    DEBUGHEXLOGSG(buffer, buflen, "hello DEBUG buffer[%ld]", buflen); /* ��һ���������Ĺ��� */
    INFOHEXLOGSG(buffer, buflen, "hello INFO buffer[%ld]", buflen);
    WARNHEXLOGSG(buffer, buflen, "hello WARN buffer[%ld]", buflen);
    ERRORHEXLOGSG(buffer, buflen, "hello ERROR buffer[%ld]", buflen);
    FATALHEXLOGSG(buffer, buflen, "hello FATAL buffer[%ld]", buflen);

    /* ������־������� */
    DestroyLogsHandleG(); /* ��־��������ڰ�����������־����������ٵ� */
    printf("�ͷ���־�������\n");

    return 0;
}
