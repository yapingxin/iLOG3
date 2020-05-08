#include "TC01_Basic_INFOLOGG.h"
#include "LOG.h"

#define LOG_STYLES_HELLO        ( LOG_STYLE_DATETIMEMS | LOG_STYLE_LOGLEVEL | LOG_STYLE_PID | LOG_STYLE_TID | LOG_STYLE_SOURCE | LOG_STYLE_FORMAT | LOG_STYLE_NEWLINE )


int TC01_Basic_INFOLOGG()
{
    char                buffer[64 + 1] = "";
    long                buflen = sizeof(buffer) - 1;

    /* ������־��� */
    if (CreateLogHandleG() == NULL)
    {
        printf("������־���ʧ��errno[%d]\n", errno);
        return -1;
    }

    /* ������־����ļ��� */
    SetLogOutputG(LOG_OUTPUT_FILE, "test_iLOG3.log", LOG_NO_OUTPUTFUNC);
    /* ���õ�ǰ��־���˵ȼ� */
    SetLogLevelG(LOG_LEVEL_INFO);
    /* ���õ�ǰ����־��񷽰� */
    SetLogStylesG(LOG_STYLES_HELLO, LOG_NO_STYLEFUNC);

    /* �Բ�ͬ��־�ȼ�д����־ */
    DEBUGLOGG("hello DEBUG"); /* ������־��ȼ��������������Ĺ����� */
    INFOLOGG("hello INFO");
    WARNLOGG("hello WARN");
    ERRORLOGG("hello ERROR");
    FATALLOGG("hello FATAL");

    /* �Բ�ͬ��־�ȼ�дʮ�����ƿ���־ */
    DEBUGHEXLOGG(buffer, buflen, "hello DEBUG buffer[%ld]", buflen); /* ��һ���������Ĺ��� */
    INFOHEXLOGG(buffer, buflen, "hello INFO buffer[%ld]", buflen);
    WARNHEXLOGG(buffer, buflen, "hello WARN buffer[%ld]", buflen);
    ERRORHEXLOGG(buffer, buflen, "hello ERROR buffer[%ld]", buflen);
    FATALHEXLOGG(buffer, buflen, "hello FATAL buffer[%ld]", buflen);

    /* ������־��� */
    DestroyLogHandleG();
    printf("�ͷ���־���\n");

    return 0;
}
