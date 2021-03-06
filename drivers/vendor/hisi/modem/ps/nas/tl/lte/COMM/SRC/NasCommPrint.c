



/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasCommPrint.h"
#include  "NasCommPublic.h"
#include  "SmEsmInterface.h"
#include  "LPsOm.h"

#include  "OmEsmInterface.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASCOMMPRINT_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASCOMMPRINT_C
/*lint +e767*/



/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
VOS_CHAR                                g_acPrintBuf[NAS_COMM_PRINT_BUFF_LEN] = "";
VOS_CHAR                                g_acEsmPrintBuf[NAS_COMM_PRINT_BUFF_LEN] = "";


/* EMM-RABM 消息打印数组 */
NAS_COMM_PRINT_MSG_LIST_STRU g_astMmRabmMsgIdArray[] =
{
    {   ID_EMM_ERABM_REEST_IND           ,
            "MSG:  ID_EMM_ERABM_REEST_IND                           "},
    {   ID_EMM_ERABM_REEST_REQ           ,
            "MSG:  ID_EMM_ERABM_REEST_REQ                           "},
    {   ID_EMM_ERABM_REL_IND             ,
            "MSG:  ID_EMM_ERABM_REL_IND                             "},
    {   ID_EMM_ERABM_DRB_SETUP_IND      ,
            "MSG:  ID_EMM_ERABM_DRB_SETUP_IND                       "},
    {   ID_EMM_ERABM_REL_REQ             ,
            "MSG:  ID_EMM_ERABM_REL_REQ                             "},
    {   ID_EMM_ERABM_RRC_CON_REL_IND     ,
            "MSG:  ID_EMM_ERABM_RRC_CON_REL_IND                     "},
    {   ID_EMM_ERABM_SUSPEND_IND     ,
            "MSG:  ID_EMM_ERABM_SUSPEND_IND                         "},
    {   ID_EMM_ERABM_SUSPEND_RSP     ,
            "MSG:  ID_EMM_ERABM_SUSPEND_RSP                         "},
    {   ID_EMM_ERABM_RESUME_IND     ,
            "MSG:  ID_EMM_ERABM_RESUME_IND                          "},
    {   ID_EMM_ERABM_RESUME_RSP     ,
            "MSG:  ID_EMM_ERABM_RESUME_RSP                          "}
};

/* SM-ESM 消息打印数组 */
NAS_COMM_PRINT_LIST_STRU g_astSmEsmMsgIdArray[] =
{
    {   ID_SM_ESM_PDP_CONTEXT_INFO_IND               ,
            "MSG:  ID_SM_ESM_PDP_CONTEXT_INFO_IND                  ",
        VOS_NULL_PTR},
    {   ID_ESM_SM_EPS_BEARER_INFO_IND               ,
            "MSG:  ID_ESM_SM_EPS_BEARER_INFO_IND                   ",
        VOS_NULL_PTR},
    {   ID_ESM_APS_ESM_NOTIFICATION_IND              ,
            "MSG:  ID_ESM_APS_ESM_NOTIFICATION_IND                 ",
        VOS_NULL_PTR}
};
/* OM-SM 消息打印数组*/
NAS_COMM_PRINT_LIST_STRU g_astOmEsmMsgIdArray[] =
{
    {   ID_OM_ESM_INFO_REPORT_REQ               ,
            "MSG:  ID_OM_ESM_INFO_REPORT_REQ                  ",
        VOS_NULL_PTR},
    {   ID_OM_ESM_INFO_REPORT_CNF               ,
            "MSG:  ID_OM_ESM_INFO_REPORT_CNF                   ",
        VOS_NULL_PTR}
};

/* EMM-ESM 消息打印数组 */
NAS_COMM_PRINT_LIST_STRU g_astMmEsmMsgIdArray[] =
{
    {   ID_EMM_ESM_EST_REQ               ,
            "MSG:  ID_EMM_ESM_EST_REQ                              ",
        VOS_NULL_PTR},
    {   ID_EMM_ESM_EST_CNF               ,
            "MSG:  ID_EMM_ESM_EST_CNF                              ",
        VOS_NULL_PTR},
    {   ID_EMM_ESM_BEARER_STATUS_REQ     ,
            "MSG:  ID_EMM_ESM_BEARER_STATUS_REQ                    ",
        NAS_COMM_PrintMmEsmBearerStatusReqOrInd},
    {   ID_EMM_ESM_STATUS_IND            ,
            "MSG:  ID_EMM_ESM_STATUS_IND                           ",
        VOS_NULL_PTR},
    {   ID_EMM_ESM_DATA_REQ              ,
            "MSG:  ID_EMM_ESM_DATA_REQ                             ",
        VOS_NULL_PTR},
    {   ID_EMM_ESM_SAVE_ERRLOG_IND              ,
            "MSG:  ID_EMM_ESM_SAVE_ERRLOG_IND                      ",
        VOS_NULL_PTR},
    {   ID_EMM_ESM_DATA_IND              ,
            "MSG:  ID_EMM_ESM_DATA_IND                             ",
        VOS_NULL_PTR},
    {   ID_EMM_ESM_REL_REQ               ,
            "MSG:  ID_EMM_ESM_REL_REQ                              ",
        VOS_NULL_PTR},
    {   ID_EMM_ESM_REL_IND               ,
            "MSG:  ID_EMM_ESM_REL_IND                              ",
        VOS_NULL_PTR},
    {   ID_EMM_ESM_PDN_CON_RSP           ,
            "MSG:  ID_EMM_ESM_PDN_CON_RSP                          ",
        VOS_NULL_PTR},
    {   ID_EMM_ESM_PDN_CON_IND           ,
        "MSG:  ID_EMM_ESM_PDN_CON_IND                              ",
        VOS_NULL_PTR},
    {   ID_EMM_ESM_BEARER_STATUS_IND     ,
            "MSG:  ID_EMM_ESM_BEARER_STATUS_IND                    ",
        NAS_COMM_PrintMmEsmBearerStatusReqOrInd},
    {   ID_EMM_ESM_PDN_CON_SUCC_REQ     ,
            "MSG:  ID_EMM_ESM_PDN_CON_SUCC_REQ                     ",
        VOS_NULL_PTR},
    {   ID_EMM_ESM_SUSPEND_IND           ,
        "MSG:  ID_EMM_ESM_SUSPEND_IND                              ",
        VOS_NULL_PTR},
    {   ID_EMM_ESM_SUSPEND_RSP           ,
        "MSG:  ID_EMM_ESM_SUSPEND_RSP                              ",
        VOS_NULL_PTR},
    {   ID_EMM_ESM_RESUME_IND           ,
        "MSG:  ID_EMM_ESM_RESUME_IND                              ",
        VOS_NULL_PTR},
    {   ID_EMM_ESM_RESUME_RSP           ,
        "MSG:  ID_EMM_ESM_RESUME_RSP                              ",
        VOS_NULL_PTR},
    {   ID_EMM_ESM_BEARER_MODIFY_REQ           ,
        "MSG:  ID_EMM_ESM_BEARER_MODIFY_REQ                       ",
        VOS_NULL_PTR},
    {   ID_EMM_ESM_CLR_ESM_PROC_RES_NOTIFY           ,
        "MSG:  ID_EMM_ESM_CLR_ESM_PROC_RES_NOTIFY                 ",
        VOS_NULL_PTR},
    {   ID_EMM_ESM_DEACT_NON_EMC_BEARER_IND           ,
        "MSG:  ID_EMM_ESM_DEACT_NON_EMC_BEARER_IND                ",
        VOS_NULL_PTR}
};

NAS_COMM_PRINT_LIST_STRU g_astEsmRabmMsgIdArray[] =
{
    /* RABM发给SM的原语 */
    {   ID_ESM_ERABM_REL_REQ               ,
        "MSG:  ID_ESM_ERABM_REL_REQ                           ",
        VOS_NULL_PTR        },
    {   ID_ESM_ERABM_BEARER_STATUS_REQ     ,
        "MSG:  ID_ESM_ERABM_BEARER_STATUS_REQ                 ",
        NAS_COMM_PrintEsmRabmBearerStatusReqMsg},

    /* SM发给RABM的原语 */
    {   ID_ESM_ERABM_ACT_IND               ,
        "MSG:  ID_ESM_ERABM_ACT_IND                           ",
        NAS_COMM_PrintEsmRabmActIndOrModIndMsg                           },
    {   ID_ESM_ERABM_MDF_IND               ,
        "MSG:  ID_ESM_ERABM_MDF_IND                           ",
        NAS_COMM_PrintEsmRabmActIndOrModIndMsg},
    {   ID_ESM_ERABM_DEACT_IND             ,
        "MSG:  ID_ESM_ERABM_DEACT_IND                         ",
        NAS_COMM_PrintEsmRabmDeactIndMsg},
    {   ID_ESM_ERABM_REL_IND               ,
        "MSG:  ID_ESM_ERABM_REL_IND                           ",
        VOS_NULL_PTR}
};

NAS_COMM_PRINT_MSG_LIST_STRU g_astRabmTcMsgIdArray[] =
{
    {   ID_ETC_ERABM_ACTIVATE_TEST_MODE               ,
            "MSG:  ID_ETC_ERABM_ACTIVATE_TEST_MODE                           "},
    {   ID_ETC_ERABM_DEACTIVATE_TEST_MODE               ,
            "MSG:  ID_ETC_ERABM_DEACTIVATE_TEST_MODE                           "},
    {   ID_ETC_ERABM_REL_REQ               ,
            "MSG:  ID_ETC_ERABM_REL_REQ                           "},
    {   ID_ETC_ERABM_REL_IND               ,
            "MSG:  ID_ETC_ERABM_REL_IND                           "},
    {   ID_ETC_ERABM_SUSPEND_IND               ,
            "MSG:  ID_ETC_ERABM_SUSPEND_IND                           "},
    {   ID_ETC_ERABM_SUSPEND_RSP               ,
            "MSG:  ID_ETC_ERABM_SUSPEND_RSP                           "},
    {   ID_ETC_ERABM_RESUME_IND               ,
            "MSG:  ID_ETC_ERABM_RESUME_IND                           "},
    {   ID_ETC_ERABM_RESUME_RSP               ,
            "MSG:  ID_ETC_ERABM_RESUME_RSP                           "}
};

NAS_COMM_PRINT_MSG_LIST_STRU g_astTcMmMsgIdArray[] =
{
    {   ID_EMM_ETC_DATA_REQ               ,
            "MSG:  ID_EMM_ETC_DATA_REQ                           "},
    {   ID_EMM_ETC_REL_REQ               ,
            "MSG:  ID_EMM_ETC_REL_REQ                           "},
    {   ID_EMM_ETC_DATA_IND               ,
            "MSG:  ID_EMM_ETC_DATA_IND                           "},
    {   ID_EMM_ETC_REL_IND               ,
            "MSG:  ID_EMM_ETC_REL_IND                           "}
};

/*****************************************************************************
  3 Function
*****************************************************************************/

/*lint -e960*/
/*lint -e961*/
VOS_VOID    NAS_COMM_nsprintf
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                              usOffset,
    const VOS_CHAR                          *String,
    VOS_INT32                               *pilOutLen
)
{
    /* delay begin */
    PS_LOG_RETURN();
    /* delay end */

    /* 入参检查 */
    if ( VOS_NULL_PTR == pilOutLen )
    {
        NAS_COMM_LOG_ERR("NAS_COMM_nsprintf, pilOutLen is NULL pointer!");
        return;
    }

    if ( VOS_NULL_PTR == pcBuff )
    {
        NAS_COMM_LOG_ERR("NAS_COMM_nsprintf, pcBuff is NULL pointer!");
        *pilOutLen = 0;
        return;
    }

    if ( VOS_NULL_PTR == String )
    {
        NAS_COMM_LOG_ERR("NAS_COMM_nsprintf, String is NULL pointer!");
        *pilOutLen = 0;
        return;
    }

    if ((NAS_COMM_PRINT_BUFF_LEN - 2) >= usOffset )
    {
        /* 需要预留一个字符作为结束符 */
        *pilOutLen = VOS_nsprintf(pcBuff + usOffset,
                                  (NAS_COMM_PRINT_BUFF_LEN - 1) - usOffset,
                                  String);
        if( (0 == *pilOutLen) || (PS_NEG_ONE == *pilOutLen) )
        {
            NAS_COMM_LOG1_WARN("NAS_COMM_nsprintf, *pilOutLen=", *pilOutLen);
            *pilOutLen = 0;
            return;
        }
    }
    else
    {

        NAS_COMM_LOG_ERR("NAS_COMM_nsprintf, Print too long!");
        *pilOutLen = 0;
        return;
    }
}


VOS_VOID    NAS_COMM_nsprintf_1
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                              usOffset,
    const VOS_CHAR                          *String,
    VOS_UINT32                               para1,
    VOS_INT32                               *pilOutLen
)
{
    /* delay begin */
    PS_LOG_RETURN();
    /* delay end */

    /* 入参检查 */
    if ( VOS_NULL_PTR == pilOutLen )
    {
        NAS_COMM_LOG_ERR("NAS_COMM_nsprintf_1, pilOutLen is NULL pointer!");
        return;
    }

    if ( VOS_NULL_PTR == pcBuff )
    {
        NAS_COMM_LOG_ERR("NAS_COMM_nsprintf_1, pcBuff is NULL pointer!");
        *pilOutLen = 0;
        return;
    }

    if ( VOS_NULL_PTR == String )
    {
        NAS_COMM_LOG_ERR("NAS_COMM_nsprintf_1, String is NULL pointer!");
        *pilOutLen = 0;
        return;
    }

    if ((NAS_COMM_PRINT_BUFF_LEN - 2) >= usOffset )
    {
        /* 需要预留一个字符作为结束符 */
        *pilOutLen = VOS_nsprintf(pcBuff + usOffset,
                                  (NAS_COMM_PRINT_BUFF_LEN - 1) - usOffset,
                                  String,
                                  para1);
        if( (0 == *pilOutLen) || (PS_NEG_ONE == *pilOutLen) )
        {
            NAS_COMM_LOG1_WARN("NAS_COMM_nsprintf_1,*pilOutLen=", *pilOutLen);
            *pilOutLen = 0;
            return;
        }
    }
    else
    {
        NAS_COMM_LOG_ERR("NAS_COMM_nsprintf_1, Print too long!");

        *pilOutLen = 0;
        return;
    }
}


VOS_VOID    NAS_COMM_nsprintf_2(
                    VOS_CHAR                                *pcBuff,
                    VOS_UINT16                              usOffset,
                    const VOS_CHAR                          *String,
                    VOS_UINT32                               para1,
                    VOS_UINT32                               para2,
                    VOS_INT32                               *pilOutLen )
{
    /* delay begin */
    PS_LOG_RETURN();
    /* delay end */

    /* 入参检查 */
    if ( VOS_NULL_PTR == pilOutLen )
    {
        NAS_COMM_LOG_ERR("NAS_COMM_nsprintf_2, pilOutLen is NULL pointer!");
        return;
    }

    if ( VOS_NULL_PTR == pcBuff )
    {
        NAS_COMM_LOG_ERR("NAS_COMM_nsprintf_2, pcBuff is NULL pointer!");
        *pilOutLen = 0;
        return;
    }

    if ( VOS_NULL_PTR == String )
    {
        NAS_COMM_LOG_ERR("NAS_COMM_nsprintf_2, String is NULL pointer!");
        *pilOutLen = 0;
        return;
    }

    if ((NAS_COMM_PRINT_BUFF_LEN - 2) >= usOffset )
    {
        /* 需要预留一个字符作为结束符 */
        *pilOutLen = VOS_nsprintf(pcBuff + usOffset,
                                  (NAS_COMM_PRINT_BUFF_LEN - 1) - usOffset,
                                  String,
                                  para1,
                                  para2);
        if( (0 == *pilOutLen) || (PS_NEG_ONE == *pilOutLen) )
        {
            NAS_COMM_LOG1_WARN("NAS_COMM_nsprintf_2,*pilOutLen=", *pilOutLen);
            *pilOutLen = 0;
            return;
        }
    }
    else
    {
        NAS_COMM_LOG_ERR("NAS_COMM_nsprintf_2, Print too long!");

        *pilOutLen = 0;
        return;
    }
}


VOS_VOID    NAS_COMM_nsprintf_3(
                    VOS_CHAR                                *pcBuff,
                    VOS_UINT16                              usOffset,
                    const VOS_CHAR                          *String,
                    VOS_UINT32                               para1,
                    VOS_UINT32                               para2,
                    VOS_UINT32                               para3,
                    VOS_INT32                               *pilOutLen )
{
    /* delay begin */
    PS_LOG_RETURN();
    /* delay end */

    /* 入参检查 */
    if ( VOS_NULL_PTR == pilOutLen )
    {
        NAS_COMM_LOG_ERR("NAS_COMM_nsprintf_3, pilOutLen is NULL pointer!");
        return;
    }

    if ( VOS_NULL_PTR == pcBuff )
    {
        NAS_COMM_LOG_ERR("NAS_COMM_nsprintf_3, pcBuff is NULL pointer!");
        *pilOutLen = 0;
        return;
    }

    if ( VOS_NULL_PTR == String )
    {
        NAS_COMM_LOG_ERR("NAS_COMM_nsprintf_3, String is NULL pointer!");
        *pilOutLen = 0;
        return;
    }

    if ((NAS_COMM_PRINT_BUFF_LEN - 2)>= usOffset )
    {
        /* 需要预留一个字符作为结束符 */
        *pilOutLen = VOS_nsprintf(pcBuff + usOffset,
                                  (NAS_COMM_PRINT_BUFF_LEN - 1) - usOffset,
                                  String,
                                  para1,
                                  para2,
                                  para3);
        if( (0 == *pilOutLen) || (PS_NEG_ONE == *pilOutLen) )
        {
            NAS_COMM_LOG1_WARN("NAS_COMM_nsprintf_3,*pilOutLen=", *pilOutLen);
            *pilOutLen = 0;
            return;
        }
    }
    else
    {
        NAS_COMM_LOG_ERR("NAS_COMM_nsprintf_3, Print too long!");

        *pilOutLen = 0;
        return;
    }
}



VOS_VOID    NAS_COMM_Print
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                              usLen
)
{
    /* delay begin */
    PS_LOG_RETURN();
    /* delay end */

    /* 入参检查 */
    if ( VOS_NULL_PTR == pcBuff )
    {
        NAS_COMM_LOG_ERR("NAS_COMM_Print, Input param is NULL pointer!");
        return;
    }

    /* 需要预留一个字符作为结束符 */
    if ( usLen >= NAS_COMM_PRINT_BUFF_LEN )
    {
        NAS_COMM_LOG1_WARN("NAS_COMM_Print,usLen=", usLen);
        return;
    }
    else
    {
        pcBuff[usLen] = '\0';
        NAS_COMM_LOG_NORM(pcBuff);
        return;
    }

}


VOS_VOID   NAS_COMM_PrintArray
(
    VOS_CHAR                                    *pcBuff,
    const VOS_UINT8                             *pucArray,
    const VOS_UINT32                             ulLen
)
{
    VOS_UINT16                          usTotalLen = 0;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usLoop = 0;
    VOS_UINT8                           ucData = 0;

    /* delay begin */
    PS_LOG_RETURN();
    /* delay end */

    /* 打印数据, 一行最多16个字节 */
    for (usLoop = 0; usLoop < ulLen; usLoop++)
    {
        if ( (0 != usLoop) && (0 == (usLoop%NAS_COMM_PRINT_MAX_BYTES_PER_LINE)) )
        {
            if(usTotalLen < NAS_COMM_PRINT_BUFF_LEN)
            {
                pcBuff[usTotalLen] = '\n';
                usTotalLen++;
            }


        }
        /*lint -e662*/
        ucData = pucArray[usLoop];/*lint !e662 !e661*/
        /*lint +e662*/
        NAS_COMM_nsprintf_1(pcBuff,
                            usTotalLen,
                            "%02x ",
                            ucData,
                           &ilOutPutLen);
        if ( 0 == ilOutPutLen )
        {
            NAS_COMM_LOG_WARN("NAS_COMM_PrintArray: Print data exception.");
            return;
        }
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }

    NAS_COMM_Print(pcBuff, usTotalLen);

    return;
}


VOS_INT32   NAS_COMM_PrintMmRabmMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    EMM_ERABM_MSG_TYPE_ENUM_UINT32            enMsgId
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMmRabmMsgNum;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulMmRabmMsgNum = sizeof(g_astMmRabmMsgIdArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulMmRabmMsgNum; ulLoop++)
    {
        if (g_astMmRabmMsgIdArray[ulLoop].ulId == enMsgId)
        {
            break;
        }
    }

    if ( ulLoop < ulMmRabmMsgNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astMmRabmMsgIdArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                               usTotalLen,
                               "[ TICK : %ld ]",
                               PS_GET_TICK(),
                              &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        NAS_COMM_LOG1_WARN("NAS_COMM_PrintMmRabmMsg, Invalid enMsgId: ",
                           enMsgId);
    }

    return (usTotalLen - usOffset);
}


VOS_INT32   NAS_COMM_PrintMmEsmMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMmEsmMsgNum;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulMmEsmMsgNum = sizeof(g_astMmEsmMsgIdArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulMmEsmMsgNum; ulLoop++)
    {
        if (pstMsg->ulMsgName == g_astMmEsmMsgIdArray[ulLoop].ulId)
        {
            break;
        }
    }

    if ( ulLoop < ulMmEsmMsgNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astMmEsmMsgIdArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                               usTotalLen,
                               "[ TICK : %ld ]",
                               PS_GET_TICK(),
                              &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        if (VOS_NULL_PTR != g_astMmEsmMsgIdArray[ulLoop].pfActionFun)
        {
            ilOutPutLen = g_astMmEsmMsgIdArray[ulLoop].pfActionFun(pcBuff,
                                                                   usTotalLen,
                                                                   pstMsg);
        }

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        NAS_COMM_LOG1_WARN("NAS_COMM_PrintMmEsmMsg, Invalid enMsgId: ",
                           pstMsg->ulMsgName);
    }

    return (usTotalLen - usOffset);
}

/*****************************************************************************
 Function Name   : NAS_COMM_PrintSmEsmMsg
 Description     : 打印收到SM消息(文件内部调用函数)
 Input           : pcBuff   -- Formatted buffer
                   usOffset -- Offset
                   enMsgId  -- EMM_ESM_MSG_TYPE_ENUM_UINT32
 Output          : None
 Return          : The number of bytes that have been stored in the output buffer pcBuff
                   If the input parameter is erroneous, the return value will be 0.

 History         :
    1.lihong00150010      2011-05-02  Draft Enact

*****************************************************************************/
VOS_INT32   NAS_COMM_PrintSmEsmMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulSmEsmMsgNum;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulSmEsmMsgNum = sizeof(g_astSmEsmMsgIdArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulSmEsmMsgNum; ulLoop++)
    {
        if (pstMsg->ulMsgName == g_astSmEsmMsgIdArray[ulLoop].ulId)
        {
            break;
        }
    }

    if ( ulLoop < ulSmEsmMsgNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astSmEsmMsgIdArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                               usTotalLen,
                               "[ TICK : %ld ]",
                               PS_GET_TICK(),
                              &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        if (VOS_NULL_PTR != g_astSmEsmMsgIdArray[ulLoop].pfActionFun)
        {
            ilOutPutLen = g_astSmEsmMsgIdArray[ulLoop].pfActionFun(pcBuff,
                                                                   usTotalLen,
                                                                   pstMsg);
        }

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        NAS_COMM_LOG1_WARN("NAS_COMM_PrintSmEsmMsg, Invalid enMsgId: ",
                           pstMsg->ulMsgName);
    }

    return (usTotalLen - usOffset);
}

/*****************************************************************************
 Function Name   : NAS_COMM_PrintSmEsmMsg
 Description     : 打印收到OM消息(文件内部调用函数)
 Input           : pcBuff   -- Formatted buffer
                   usOffset -- Offset
                   enMsgId  -- EMM_ESM_MSG_TYPE_ENUM_UINT32
 Output          : None
 Return          : The number of bytes that have been stored in the output buffer pcBuff
                   If the input parameter is erroneous, the return value will be 0.

 History         :
    1.lihong00150010      2011-05-02  Draft Enact

*****************************************************************************/
VOS_INT32   NAS_COMM_PrintOmEsmMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulOmEsmMsgNum;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulOmEsmMsgNum = sizeof(g_astOmEsmMsgIdArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulOmEsmMsgNum; ulLoop++)
    {
        if (pstMsg->ulMsgName == g_astOmEsmMsgIdArray[ulLoop].ulId)
        {
            break;
        }
    }

    if ( ulLoop < ulOmEsmMsgNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astOmEsmMsgIdArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                               usTotalLen,
                               "[ TICK : %ld ]",
                               PS_GET_TICK(),
                              &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        if (VOS_NULL_PTR != g_astOmEsmMsgIdArray[ulLoop].pfActionFun)
        {
            ilOutPutLen = g_astOmEsmMsgIdArray[ulLoop].pfActionFun(pcBuff,
                                                                   usTotalLen,
                                                                   pstMsg);
        }

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        NAS_COMM_LOG1_WARN("NAS_COMM_PrintOmEsmMsg, Invalid enMsgId: ",
                           pstMsg->ulMsgName);
    }

    return (usTotalLen - usOffset);
}



VOS_INT32  NAS_COMM_PrintEsmRabmMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    const PS_MSG_HEADER_STRU            *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMmAppMsgNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    /* 获得消息表的长度 */
    ulMmAppMsgNum = sizeof(g_astEsmRabmMsgIdArray)/sizeof(NAS_COMM_PRINT_LIST_STRU);

    /* 查找对应的消息 */
    for (ulLoop = 0; ulLoop< ulMmAppMsgNum ; ulLoop++)
    {
        if (pstMsg->ulMsgName == g_astEsmRabmMsgIdArray[ulLoop].ulId)
        {
            break;
        }
    }

    /* 打印对应的消息 */
    if ( ulLoop < ulMmAppMsgNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astEsmRabmMsgIdArray[ulLoop].aucPrintString),
                   &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                               usTotalLen,
                               "[ TICK : %ld ]",
                               PS_GET_TICK(),
                              &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        if (VOS_NULL_PTR != g_astEsmRabmMsgIdArray[ulLoop].pfActionFun)
        {
            ilOutPutLen = g_astEsmRabmMsgIdArray[ulLoop].pfActionFun(pcBuff,
                                                                     usTotalLen,
                                                                     pstMsg);
        }

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        NAS_COMM_LOG1_WARN("NAS_COMM_PrintEsmRabmMsg, Invalid enMsgId: ",pstMsg->ulMsgName);
    }


    return (usTotalLen - usOffset);
}
VOS_INT32  NAS_COMM_PrintMmEsmBearerStatusReqOrInd
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen  = usOffset;
    VOS_UINT32                          ulLoop      = 0;
    VOS_CHAR                           *pcPrintStr  = VOS_NULL_PTR;
    EMM_ESM_BEARER_STATUS_REQ_STRU     *pstRcvMsg   = VOS_NULL_PTR;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    pstRcvMsg = (VOS_VOID *)pstMsg;

    if (ID_EMM_ESM_BEARER_STATUS_REQ == pstRcvMsg->ulMsgId)
    {
        pcPrintStr =  "\r\n ****************Begin :EMM_ESM_BEARER_STATUS_REQ_STRU****************\r\n";
    }
    else
    {
        pcPrintStr =  "\r\n ****************Begin :EMM_ESM_BEARER_STATUS_IND_STRU****************\r\n";
    }

    /* 打印消息结构标题 */
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     pcPrintStr,
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印消息的每个数据*/
    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " ulEpsIdNum = %d \r\n",
                       pstRcvMsg->ulEpsIdNum,
                      &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    for (ulLoop = 0; ulLoop < pstRcvMsg->ulEpsIdNum; ulLoop++)
    {
        NAS_COMM_nsprintf_2(pcBuff,
                           usTotalLen,
                           " aulEpsId[%d] = %d \r\n",
                           ulLoop,
                           pstRcvMsg->aulEsmEpsId[ulLoop],
                          &ilOutPutLen);

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }

    if (ID_EMM_ESM_BEARER_STATUS_REQ == pstRcvMsg->ulMsgId)
    {
        pcPrintStr =  " ****************End :EMM_ESM_BEARER_STATUS_REQ_STRU****************";
    }
    else
    {
        pcPrintStr =  " ****************End :EMM_ESM_BEARER_STATUS_IND_STRU****************";
    }

    /* 打印消息的结束标题*/
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     pcPrintStr,
                    &ilOutPutLen);

   usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset) ;
}
VOS_INT32  NAS_COMM_PrintRabmTcMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    ETC_ERABM_MSG_TYPE_ENUM_UINT32         enMsgId
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulRabmTcMsgNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    /* 获得消息表的长度 */
    ulRabmTcMsgNum = sizeof(g_astRabmTcMsgIdArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    /* 查找对应的消息 */
    for (ulLoop = 0; ulLoop< ulRabmTcMsgNum ; ulLoop++)
    {
        if (enMsgId == g_astRabmTcMsgIdArray[ulLoop].ulId)
        {
            break;
        }
    }

    /* 打印对应的消息 */
    if ( ulLoop < ulRabmTcMsgNum )
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         (VOS_CHAR *)(g_astRabmTcMsgIdArray[ulLoop].aucPrintString),
                         &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                               usTotalLen,
                               "[ TICK : %ld ]",
                               PS_GET_TICK(),
                              &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        NAS_COMM_LOG1_WARN("NAS_COMM_PrintRabmTcMsg, Invalid enMsgId: ",enMsgId);
    }

    return (usTotalLen - usOffset);

}
VOS_INT32  NAS_COMM_PrintMmTcMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    EMM_ETC_MSG_TYPE_ENUM_UINT32          enMsgId
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulTcMmMsgNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    /* 获得消息表的长度 */
    ulTcMmMsgNum = sizeof(g_astTcMmMsgIdArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    /* 查找对应的消息 */
    for (ulLoop = 0; ulLoop< ulTcMmMsgNum ; ulLoop++)
    {
        if (enMsgId == g_astTcMmMsgIdArray[ulLoop].ulId)
        {
            break;
        }
    }

    /* 打印对应的消息 */
    if ( ulLoop < ulTcMmMsgNum )
    {
        NAS_COMM_nsprintf(
                     pcBuff,
                     usOffset,
                     (VOS_CHAR *)(g_astTcMmMsgIdArray[ulLoop].aucPrintString),
                     &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                               usTotalLen,
                               "[ TICK : %ld ]",
                               PS_GET_TICK(),
                              &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        NAS_COMM_LOG1_WARN("NAS_COMM_PrintMmTcMsg, Invalid enMsgId: ",enMsgId);
    }

    return (usTotalLen - usOffset);

}
VOS_INT32  NAS_COMM_PrintEsmRabmBearerStatusReqMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen  = usOffset;
    VOS_UINT32                          ulLoop      = 0;
    ESM_ERABM_BEARER_STATUS_REQ_STRU    *pstRcvMsg   = VOS_NULL_PTR;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    pstRcvMsg = (VOS_VOID *)pstMsg;


    /* 打印消息结构标题 */
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "\r\n ****************Begin :ESM_ERABM_BEARER_STATUS_REQ_STRU****************\r\n",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印消息的每个数据*/
    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " ulEpsIdNum = %d \r\n",
                       pstRcvMsg->ulEpsIdNum,
                      &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    for (ulLoop = 0; ulLoop < pstRcvMsg->ulEpsIdNum; ulLoop++)
    {
        NAS_COMM_nsprintf_2(pcBuff,
                           usTotalLen,
                           " aulEpsId[%d] = %d \r\n",
                           ulLoop,
                           pstRcvMsg->aulEpsId[ulLoop],
                           &ilOutPutLen);

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }

    /* 打印消息的结束标题*/
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     " ****************End :ESM_ERABM_BEARER_STATUS_REQ_STRU****************",
                    &ilOutPutLen);

   usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset) ;
}
VOS_INT32  NAS_COMM_PrintEsmRabmActIndOrModIndMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen  = usOffset;
    VOS_CHAR                           *pcPrintStr  = VOS_NULL_PTR;
    ESM_ERABM_ACT_IND_STRU              *pstRcvMsg   = VOS_NULL_PTR;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    pstRcvMsg = (VOS_VOID *)pstMsg;

    if (ID_ESM_ERABM_ACT_IND == pstRcvMsg->ulMsgId)
    {
        pcPrintStr =  "\r\n ****************Begin :ESM_ERABM_ACT_IND_STRU****************\r\n";
    }
    else
    {
        pcPrintStr =  "\r\n ****************Begin :ESM_ERABM_MDF_IND_STRU****************\r\n";
    }

    /* 打印消息结构标题 */
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     pcPrintStr,
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印消息的每个数据*/
    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " ulEpsId = %d \r\n",
                       pstRcvMsg->ulEpsId,
                      &ilOutPutLen);
    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " ulTftPfNum = %d \r\n",
                       pstRcvMsg->ulTftPfNum,
                      &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印消息的结束标题*/
    if (ID_ESM_ERABM_ACT_IND == pstRcvMsg->ulMsgId)
    {
        pcPrintStr =  " ****************End :ESM_ERABM_ACT_IND_STRU****************";
    }
    else
    {
        pcPrintStr =  " ****************End :ESM_ERABM_MDF_IND_STRU****************";
    }

    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     pcPrintStr,
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset) ;

}
VOS_INT32  NAS_COMM_PrintEsmRabmDeactIndMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen  = usOffset;
    VOS_UINT32                          ulLoop      = 0;
    ESM_ERABM_DEACT_IND_STRU            *pstRcvMsg   = VOS_NULL_PTR;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    pstRcvMsg = (VOS_VOID *)pstMsg;


    /* 打印消息结构标题 */
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "\r\n ****************Begin :ESM_ERABM_DEACT_IND_STRU****************\r\n",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印消息的每个数据*/
    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " ulEpsIdNum = %d \r\n",
                       pstRcvMsg->ulEpsIdNum,
                      &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    for (ulLoop = 0; ulLoop < pstRcvMsg->ulEpsIdNum; ulLoop++)
    {
        NAS_COMM_nsprintf_2(pcBuff,
                           usTotalLen,
                           " aulEpsId[%d] = %d \r\n",
                           ulLoop,
                           pstRcvMsg->aulEpsId[ulLoop],
                          &ilOutPutLen);

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }

    /* 打印消息的结束标题*/
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     " ****************End :ESM_ERABM_DEACT_IND_STRU****************",
                    &ilOutPutLen);

   usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset) ;
}
/*lint +e961*/
/*lint +e960*/
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

