



/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasEsmTest.h"
#include  "NasLmmTest.h"
#include  "NasERabmTest.h"
#if (VOS_OS_VER != VOS_WIN32)
#include  "LPsOm.h"
#endif

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASESMTEST_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASESMTEST_C
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
/* ESM状态机定时器打印数组 */
NAS_ESM_TIMER_PRINT_LIST_STRU g_astEsmTimerArray[] =
{
    {   TI_NAS_ESM_T3480         ,
            "定时器T3480信息如下:"       },
    {   TI_NAS_ESM_T3481         ,
            "定时器T3481信息如下:"       },
    {   TI_NAS_ESM_T3482         ,
            "定时器T3482信息如下:"       },
    {   TI_NAS_ESM_T3492         ,
            "定时器T3492信息如下:"       },
    {   TI_NAS_ESM_WAIT_APP_CNF  ,
            "等待APP响应定时器信息如下:" },
    {   TI_NAS_ESM_ATTACH_BEARER_REEST,
            "等待注册承载重建应定时器信息如下:" },
};

/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name   : NAS_ESM_DebugInit
 Description     : ESM软调初始化
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-03-10  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_DebugInit(VOS_VOID)
{
    return ;
}


VOS_VOID NAS_ESM_ShowQos(const APP_ESM_EPS_QOS_INFO_STRU *pstSdfQos)
{

    vos_printf("QoS信息如下:\r\n");
    vos_printf("%-30s : %d\r\n","QCI值",pstSdfQos->ucQCI);
    vos_printf("%-30s : %dkbps\r\n","上行最大速率     ulULMaxRate",pstSdfQos->ulULMaxRate);
    vos_printf("%-30s : %dkbps\r\n","下行最大速率     ulDLMaxRate",pstSdfQos->ulDLMaxRate);
    vos_printf("%-30s : %dkbps\r\n","上行保证最大速率 ulULGMaxRate",pstSdfQos->ulULGMaxRate);
    vos_printf("%-30s : %dkbps\r\n","下行保证最大速率 ulDLGMaxRate",pstSdfQos->ulDLGMaxRate);
}

/*****************************************************************************
 Function Name   : NAS_ESM_ShowCidInfoQos
 Description     : 打印CID信息中的QOS信息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-1-18  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_ShowCidInfoQos(const NAS_ESM_SDF_PARA_STRU *pstSdfPara)
{
    if ( NAS_ESM_OP_TRUE == pstSdfPara->bitOpSdfQos )
    {
        NAS_ESM_ShowQos(&(pstSdfPara->stSdfQosInfo));
    }
    else
    {
        vos_printf("%-30s\r\n","该CID不存在SDF QoS");
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_ShowEpsQos
 Description     : 打印ESP承载的QOS信息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-1-18  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_ShowEpsQos( const NAS_ESM_EPSB_CNTXT_INFO_STRU *pstEpsbInfo )
{
    if(NAS_ESM_OP_TRUE == pstEpsbInfo->bitOpEpsQos )
    {
        NAS_ESM_ShowQos(&(pstEpsbInfo->stEpsQoSInfo.stQosInfo));
    }
    else
    {
        vos_printf("该承载不存在QoS信息\r\n");
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_ShowLinkEpsbId
 Description     : 打印关联缺省承载号
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-1-18  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_ShowLinkEpsbId( VOS_UINT32 ulLinkEpsbId )
{
    if ( (ulLinkEpsbId < NAS_ESM_MIN_EPSB_ID) || (ulLinkEpsbId > NAS_ESM_MAX_EPSB_ID) )
    {
        vos_printf("%-30s\r\n","不存在关联EPSBID");
    }
    else
    {
        vos_printf("%-30s : %d\r\n","关联EPSBID",ulLinkEpsbId);
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_ShowBearerManagementType
 Description     : 打印承载管理方式
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-1-18  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_ShowBearerManagementType(  )
{
    NAS_ESM_PDP_MANAGE_INFO_STRU stBearerManType = pg_stNasEsmEntity->stEsmBearerManageInfo;

    if ((stBearerManType.enMode != NAS_ESM_BEARER_MANAGE_MODE_AUTO)
        && (stBearerManType.enMode != NAS_ESM_BEARER_MANAGE_MODE_MANUAL))
    {
        vos_printf("承载管理方式无法识别!\r\n");
        return ;
    }

    if (stBearerManType.enMode == NAS_ESM_BEARER_MANAGE_MODE_MANUAL)
    {
        vos_printf("%-30s : %s\r\n","承载管理方式","手动");
        return ;
    }

    if (stBearerManType.enType == NAS_ESM_BEARER_MANAGE_TYPE_ACCEPT)
    {
        vos_printf("%-30s : %s\r\n","承载管理方式","自动接受");
    }
    else if (stBearerManType.enType == NAS_ESM_BEARER_MANAGE_TYPE_REJ)
    {
        vos_printf("%-30s : %s\r\n","承载管理方式","自动拒绝");
    }
    else
    {
        vos_printf("承载管理方式无法识别!\r\n");
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_ShowEpsSdfId
 Description     : 打印承载包含的SDF号
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-1-18  Draft Enact

*****************************************************************************/
/*lint -e960*/
VOS_VOID NAS_ESM_ShowEpsSdfId( const NAS_ESM_EPSB_CNTXT_INFO_STRU *pstEpsbInfo )
{
    VOS_UINT32                          ulBitCId    = NAS_ESM_NULL;
    VOS_UINT8                           ucLoop      = NAS_ESM_NULL;
    PS_BOOL_ENUM_UINT8                  enIsFirSdf  = PS_TRUE;

    if(NAS_ESM_OP_TRUE != pstEpsbInfo->bitOpCId )
    {
         vos_printf("此承载下不包含SDF\r\n");
         return ;
    }

    ulBitCId = pstEpsbInfo->ulBitCId;

    vos_printf("%-30s : ","该承载包含的SDF的CID号");

    for (ucLoop = NAS_ESM_MIN_CID; ucLoop <= NAS_ESM_MAX_CID; ucLoop++)
    {
        if (NAS_ESM_OP_TRUE != ((ulBitCId >> ucLoop) & NAS_ESM_BIT_0))
        {
            continue;
        }

        if (PS_TRUE == enIsFirSdf)
        {
            vos_printf("%d",ucLoop);
            enIsFirSdf = PS_FALSE;
        }
        else
        {
            vos_printf(",%d",ucLoop);
        }
    }

    vos_printf("\r\n");
}
VOS_VOID NAS_ESM_ShowLinkCid(const NAS_ESM_SDF_PARA_STRU *pstSdfPara)
{
    if (NAS_ESM_OP_TRUE == pstSdfPara->bitOpLinkdCId)
    {
        vos_printf("%-30s : %d\r\n","关联cid",pstSdfPara->ulLinkdCId);
    }
    else
    {
        vos_printf("不存在关联cid\r\n");
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_ShowCidInfoTft
 Description     : 打印TFT信息
 Input           : pstBearerPara------------
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-01-18  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_ShowTft
(
    VOS_UINT32                          ulPfNum,
    NAS_ESM_CONTEXT_TFT_STRU		   *pstTft
)
{
    NAS_ESM_CONTEXT_TFT_STRU           *pstTftTmp   = VOS_NULL_PTR;
    VOS_UINT32                          ulLoop      = NAS_ESM_NULL;

    if ( NAS_ESM_NULL == ulPfNum )
    {
        vos_printf("不存在PF信息\r\n");
        return;
    }
    else
    {
        vos_printf("存在%d个PF\r\n",ulPfNum);
    }

    for ( ulLoop = 0 ; ulLoop < ulPfNum; ulLoop++ )
    {
        pstTftTmp = pstTft + ulLoop;

        vos_printf("*******************第%d个PF信息*******************\r\n",(ulLoop + 1));

        vos_printf("%-30s : %d\r\n","过滤器的本地ID",pstTftTmp->ucPacketFilterId);
        vos_printf("%-30s : %d\r\n","过滤器的网侧分配ID",pstTftTmp->ucNwPacketFilterId);

        vos_printf("%-30s : %d\r\n","PF的优先级", pstTftTmp->ucPrecedence);

        if ( NAS_ESM_OP_TRUE == pstTftTmp->bitOpRmtIpv4AddrAndMask )
        {
            vos_printf("%-30s : %d.%d.%d.%d\r\n","PF的目的IPv4", pstTftTmp->aucRmtIpv4Address[0],
                                      pstTftTmp->aucRmtIpv4Address[1],
                                      pstTftTmp->aucRmtIpv4Address[2],
                                      pstTftTmp->aucRmtIpv4Address[3]);

            vos_printf("%-30s : %d.%d.%d.%d\r\n","PF的掩码", pstTftTmp->aucRmtIpv4Mask[0],
                                      pstTftTmp->aucRmtIpv4Mask[1],
                                      pstTftTmp->aucRmtIpv4Mask[2],
                                      pstTftTmp->aucRmtIpv4Mask[3]);
        }

        if ( NAS_ESM_OP_TRUE == pstTftTmp->bitOpRmtIpv6AddrAndMask )
        {
            vos_printf("%-30s : %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n","PF的目的IPv6",
                                      pstTftTmp->aucRmtIpv6Address[0],
                                      pstTftTmp->aucRmtIpv6Address[1],
                                      pstTftTmp->aucRmtIpv6Address[2],
                                      pstTftTmp->aucRmtIpv6Address[3],
                                      pstTftTmp->aucRmtIpv6Address[4],
                                      pstTftTmp->aucRmtIpv6Address[5],
                                      pstTftTmp->aucRmtIpv6Address[6],
                                      pstTftTmp->aucRmtIpv6Address[7],
                                      pstTftTmp->aucRmtIpv6Address[8],
                                      pstTftTmp->aucRmtIpv6Address[9],
                                      pstTftTmp->aucRmtIpv6Address[10],
                                      pstTftTmp->aucRmtIpv6Address[11],
                                      pstTftTmp->aucRmtIpv6Address[12],
                                      pstTftTmp->aucRmtIpv6Address[13],
                                      pstTftTmp->aucRmtIpv6Address[14],
                                      pstTftTmp->aucRmtIpv6Address[15]);

            vos_printf("%-30s : %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n","PF的掩码",
                                      pstTftTmp->aucRmtIpv6Mask[0],
                                      pstTftTmp->aucRmtIpv6Mask[1],
                                      pstTftTmp->aucRmtIpv6Mask[2],
                                      pstTftTmp->aucRmtIpv6Mask[3],
                                      pstTftTmp->aucRmtIpv6Mask[4],
                                      pstTftTmp->aucRmtIpv6Mask[5],
                                      pstTftTmp->aucRmtIpv6Mask[6],
                                      pstTftTmp->aucRmtIpv6Mask[7],
                                      pstTftTmp->aucRmtIpv6Mask[8],
                                      pstTftTmp->aucRmtIpv6Mask[9],
                                      pstTftTmp->aucRmtIpv6Mask[10],
                                      pstTftTmp->aucRmtIpv6Mask[11],
                                      pstTftTmp->aucRmtIpv6Mask[12],
                                      pstTftTmp->aucRmtIpv6Mask[13],
                                      pstTftTmp->aucRmtIpv6Mask[14],
                                      pstTftTmp->aucRmtIpv6Mask[15]);
        }

        if ( NAS_ESM_OP_TRUE == pstTftTmp->bitOpLocalPortRange )
        {
            vos_printf("%-30s : %d\r\n","PF的近端端口最小值", pstTftTmp->usLcPortLowLimit);
            vos_printf("%-30s : %d\r\n","PF的近端端口最大值", pstTftTmp->usLcPortHighLimit);
        }

        if ( NAS_ESM_OP_TRUE == pstTftTmp->bitOpRemotePortRange)
        {
            vos_printf("%-30s : %d\r\n","PF的远端端口最小值", pstTftTmp->usRmtPortLowLimit);
            vos_printf("%-30s : %d\r\n","PF的远端端口最大值", pstTftTmp->usRmtPortHighLimit);
        }

        if (NAS_ESM_OP_TRUE == pstTftTmp->bitOpProtocolId)
        {
            vos_printf("%-30s : %d\r\n","PF的协议版本号", pstTftTmp->ucProtocolId);
        }

        if ( NAS_ESM_OP_TRUE == pstTftTmp->bitOpSingleLocalPort)
        {
            vos_printf("%-30s : %d\r\n","PF的近端端口号", pstTftTmp->usSingleLcPort);
        }

        if ( NAS_ESM_OP_TRUE == pstTftTmp->bitOpSingleRemotePort)
        {
            vos_printf("%-30s : %d\r\n","PF的远端端口号", pstTftTmp->usSingleRmtPort);
        }

    }
}


VOS_VOID NAS_ESM_ShowPdnTpe(const NAS_ESM_SDF_PARA_STRU *pstSdfPara)
{
    if (NAS_ESM_OP_TRUE == pstSdfPara->bitOpPdnType)
    {
        if(APP_ESM_PDN_TYPE_IPV4 == pstSdfPara->enPdnType)
        {
            vos_printf("%-30s : %s\r\n","PDN类型","ipv4");
        }
        else if(APP_ESM_PDN_TYPE_IPV6 == pstSdfPara->enPdnType)
        {
            vos_printf("%-30s : %s\r\n","PDN类型","ipv6");
        }
        else if(APP_ESM_PDN_TYPE_IPV4_IPV6 == pstSdfPara->enPdnType)
        {
            vos_printf("%-30s : %s\r\n","PDN类型","ipv4v6");
        }
        else
        {
            vos_printf("PDN类型错误\r\n");
        }
    }
    else
    {
        vos_printf("不存在PDN类型\r\n");
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_ShowIpAllocType
 Description     : 打印IP信息获取方式
 Input           : pstSdfPara
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-1-18  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_ShowIpAllocType(const NAS_ESM_SDF_PARA_STRU *pstSdfPara)
{
    if (NAS_ESM_OP_TRUE == pstSdfPara->bitIpv4AddrAllocType)
    {
        if (pstSdfPara->enIpv4AddrAllocType == APP_ESM_IPV4_ADDR_ALLOC_TYPE_NAS_SIGNALING)
        {
            vos_printf("%-30s : %s\r\n","IP获取方式","NAS信令");
        }
        else
        {
            vos_printf("%-30s : %s\r\n","IP获取方式","DHCP");
        }
    }
    else
    {
        vos_printf("不存在IP获取方式\r\n");
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_ShowEpsApnAmbr
 Description     : 打印承载信息中的APN-AMBR信息
 Input           : pstEpsbInfo
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010    2010-01-19  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_ShowEpsApnAmbr( const NAS_ESM_EPSB_CNTXT_INFO_STRU *pstEpsbInfo )
{
    if ((PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(pstEpsbInfo->enBearerCntxtType))
        && (NAS_ESM_OP_TRUE == pstEpsbInfo->bitOpApnAmbr))
    {
        vos_printf("APN-AMBR信息如下\r\n");
        vos_printf("%-30s : %d\r\n","DLApnAmbr",pstEpsbInfo->stApnAmbrInfo.ucDLApnAmbr);
        vos_printf("%-30s : %d\r\n","DLApnAmbrExt",pstEpsbInfo->stApnAmbrInfo.ucDLApnAmbrExt);
        vos_printf("%-30s : %d\r\n","DLApnAmbrExt2",pstEpsbInfo->stApnAmbrInfo.ucDLApnAmbrExt2);
        vos_printf("%-30s : %d\r\n","ULApnAmbr",pstEpsbInfo->stApnAmbrInfo.ucULApnAmbr);
        vos_printf("%-30s : %d\r\n","ULApnAmbrExt",pstEpsbInfo->stApnAmbrInfo.ucULApnAmbrExt);
        vos_printf("%-30s : %d\r\n","ULApnAmbrExt2",pstEpsbInfo->stApnAmbrInfo.ucULApnAmbrExt2);
    }
    else
    {
        vos_printf("不存在APN-AMBR\r\n");
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_ShowEpsApn
 Description     : 打印承载信息中的APN信息
 Input           : pstEpsbInfo
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010    2010-01-19  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_ShowEpsApn( const NAS_ESM_EPSB_CNTXT_INFO_STRU *pstEpsbInfo )
{
    VOS_UINT8                           aucApn[APP_MAX_APN_LEN];

    if ((PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(pstEpsbInfo->enBearerCntxtType))
        && (NAS_ESM_OP_TRUE == pstEpsbInfo->bitOpApn))
    {
        NAS_ESM_MEM_CPY(aucApn, pstEpsbInfo->stApnInfo.aucApnName, pstEpsbInfo->stApnInfo.ucApnLen);
        aucApn[pstEpsbInfo->stApnInfo.ucApnLen] = '\0';

        vos_printf("存在APN,APN信息如下\r\n");
        vos_printf("%-30s : %d\r\n","APN长度",pstEpsbInfo->stApnInfo.ucApnLen);
        vos_printf("%-30s : %s\r\n","APN名称",aucApn);
    }
    else
    {
        vos_printf("不存在APN\r\n");
    }
}


VOS_VOID NAS_ESM_ShowCidInfoApn(const NAS_ESM_SDF_PARA_STRU *pstSdfPara)
{
    VOS_UINT8                           aucApn[APP_MAX_APN_LEN];

    if ((PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(pstSdfPara->enBearerCntxtType))
        && (NAS_ESM_OP_TRUE == pstSdfPara->bitOpApn))
    {
        NAS_ESM_MEM_CPY(aucApn, pstSdfPara->stApnInfo.aucApnName, pstSdfPara->stApnInfo.ucApnLen);
        aucApn[pstSdfPara->stApnInfo.ucApnLen] = '\0';

        vos_printf("存在APN,APN信息如下\r\n");
        vos_printf("%-30s : %d\r\n","APN长度",pstSdfPara->stApnInfo.ucApnLen);
        vos_printf("%-30s : %s\r\n","APN名称",aucApn);
    }
    else
    {
        vos_printf("不存在APN\r\n");
    }
}
/*lint +e960*/
/*****************************************************************************
 Function Name   : NAS_ESM_ShowEpsPdn
 Description     : 打印承载信息中的PDN信息
 Input           : pstEpsbInfo
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010    2010-01-19  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_ShowEpsPdn( const NAS_ESM_EPSB_CNTXT_INFO_STRU *pstEpsbInfo )
{
    if ((PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(pstEpsbInfo->enBearerCntxtType))
        && (NAS_ESM_OP_TRUE == pstEpsbInfo->bitOpPdnAddr))
    {
        if (( APP_ESM_PDN_TYPE_IPV4 == pstEpsbInfo->stPdnAddrInfo.ucIpType )
                || ( APP_ESM_PDN_TYPE_IPV4_IPV6 == pstEpsbInfo->stPdnAddrInfo.ucIpType ))
        {
            vos_printf("%-30s : %s\r\n","PDN类型","IPv4");
            vos_printf("%-30s : %d.%d.%d.%d\r\n",
            "IP地址",
            pstEpsbInfo->stPdnAddrInfo.aucIpV4Addr[0],
            pstEpsbInfo->stPdnAddrInfo.aucIpV4Addr[1],
            pstEpsbInfo->stPdnAddrInfo.aucIpV4Addr[2],
            pstEpsbInfo->stPdnAddrInfo.aucIpV4Addr[3]);
        }
        if (( APP_ESM_PDN_TYPE_IPV6 == pstEpsbInfo->stPdnAddrInfo.ucIpType )
                || ( APP_ESM_PDN_TYPE_IPV4_IPV6 == pstEpsbInfo->stPdnAddrInfo.ucIpType ))
        {
            vos_printf("%-30s : %s\r\n","PDN类型","IPv6");
            vos_printf("%-30s : %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\r\n",
            "IP地址",
            pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[0],
            pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[1],
            pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[2],
            pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[3],
            pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[4],
            pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[5],
            pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[6],
            pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[7],
            pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[8],
            pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[9],
            pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[10],
            pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[11],
            pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[12],
            pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[13],
            pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[14],
            pstEpsbInfo->stPdnAddrInfo.aucIpV6Addr[15]);
        }
    }
    else
    {
        vos_printf("不存在PDN\r\n");
    }
}


/*lint -e960*/
VOS_VOID NAS_ESM_ShowUeIp()
{
    VOS_UINT8                           ucIpType;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulEpsbIndex;
    VOS_UINT32                          ulIndex             = 0;

    for ( ulLoop = NAS_ESM_MIN_EPSB_ID; ulLoop <= NAS_ESM_MAX_EPSB_ID; ulLoop++ )
    {
        if ((NAS_ESM_BEARER_STATE_ACTIVE == NAS_ESM_GetBearCntxtState(ulLoop))
             && (PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(NAS_ESM_GetBearCntxtType(ulLoop))))
        {
            ulEpsbIndex = ulLoop - NAS_ESM_MIN_EPSB_ID;
            ucIpType = pg_stNasEsmEntity->astEpsbCntxtInfo[ulEpsbIndex].stPdnAddrInfo.ucIpType;
            if ( (APP_ESM_PDN_TYPE_IPV4 == ucIpType) || (APP_ESM_PDN_TYPE_IPV4_IPV6 == ucIpType))
            {
                vos_printf("UE的IP地址%d                    : %d.%d.%d.%d\r\n",
                ++ulIndex,
                pg_stNasEsmEntity->astEpsbCntxtInfo[ulEpsbIndex].stPdnAddrInfo.aucIpV4Addr[0],
                pg_stNasEsmEntity->astEpsbCntxtInfo[ulEpsbIndex].stPdnAddrInfo.aucIpV4Addr[1],
                pg_stNasEsmEntity->astEpsbCntxtInfo[ulEpsbIndex].stPdnAddrInfo.aucIpV4Addr[2],
                pg_stNasEsmEntity->astEpsbCntxtInfo[ulEpsbIndex].stPdnAddrInfo.aucIpV4Addr[3]);
            }
            else if ((APP_ESM_PDN_TYPE_IPV6 == ucIpType) || (APP_ESM_PDN_TYPE_IPV4_IPV6 == ucIpType))
            {
                vos_printf("UE的IP地址%d                    : %d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d\r\n",
                ++ulIndex,
                pg_stNasEsmEntity->astEpsbCntxtInfo[ulEpsbIndex].stPdnAddrInfo.aucIpV6Addr[0],
                pg_stNasEsmEntity->astEpsbCntxtInfo[ulEpsbIndex].stPdnAddrInfo.aucIpV6Addr[1],
                pg_stNasEsmEntity->astEpsbCntxtInfo[ulEpsbIndex].stPdnAddrInfo.aucIpV6Addr[2],
                pg_stNasEsmEntity->astEpsbCntxtInfo[ulEpsbIndex].stPdnAddrInfo.aucIpV6Addr[3],
                pg_stNasEsmEntity->astEpsbCntxtInfo[ulEpsbIndex].stPdnAddrInfo.aucIpV6Addr[4],
                pg_stNasEsmEntity->astEpsbCntxtInfo[ulEpsbIndex].stPdnAddrInfo.aucIpV6Addr[5],
                pg_stNasEsmEntity->astEpsbCntxtInfo[ulEpsbIndex].stPdnAddrInfo.aucIpV6Addr[6],
                pg_stNasEsmEntity->astEpsbCntxtInfo[ulEpsbIndex].stPdnAddrInfo.aucIpV6Addr[7],
                pg_stNasEsmEntity->astEpsbCntxtInfo[ulEpsbIndex].stPdnAddrInfo.aucIpV6Addr[8],
                pg_stNasEsmEntity->astEpsbCntxtInfo[ulEpsbIndex].stPdnAddrInfo.aucIpV6Addr[9],
                pg_stNasEsmEntity->astEpsbCntxtInfo[ulEpsbIndex].stPdnAddrInfo.aucIpV6Addr[10],
                pg_stNasEsmEntity->astEpsbCntxtInfo[ulEpsbIndex].stPdnAddrInfo.aucIpV6Addr[11],
                pg_stNasEsmEntity->astEpsbCntxtInfo[ulEpsbIndex].stPdnAddrInfo.aucIpV6Addr[12],
                pg_stNasEsmEntity->astEpsbCntxtInfo[ulEpsbIndex].stPdnAddrInfo.aucIpV6Addr[13],
                pg_stNasEsmEntity->astEpsbCntxtInfo[ulEpsbIndex].stPdnAddrInfo.aucIpV6Addr[14],
                pg_stNasEsmEntity->astEpsbCntxtInfo[ulEpsbIndex].stPdnAddrInfo.aucIpV6Addr[15]);
            }
            else
            {
                vos_printf("IP地址类型错误\r\n");
            }
        }
    }
}
VOS_VOID NAS_ESM_ShowRegisterStatus(  )
{
    if (NAS_ESM_PS_REGISTER_STATUS_ATTACHED == pg_stNasEsmEntity->enRegisterStatus)
    {
        vos_printf("%-30s : %s\r\n","注册状态","已注册");
    }
    else if (NAS_ESM_PS_REGISTER_STATUS_DETACHED == pg_stNasEsmEntity->enRegisterStatus)
    {
        vos_printf("%-30s : %s\r\n","注册状态","未注册");
    }
    else
    {
        vos_printf("%-30s : %s\r\n","注册状态","注册中");
    }
}


VOS_VOID NAS_ESM_ShowBearerState(NAS_ESM_BEARER_STATE_ENUM_UINT8 enBearerCntxtState)
{
    if(NAS_ESM_BEARER_STATE_ACTIVE == enBearerCntxtState )
    {
        vos_printf("%-30s : %s\r\n","承载状态","激活态");
    }
    else
    {
        vos_printf("%-30s : %s\r\n","承载状态","非激活态");
    }
}


VOS_VOID NAS_ESM_ShowBearerType(NAS_ESM_BEARER_TYPE_ENUM_UINT8 enBearerCntxtType)
{
    if(NAS_ESM_BEARER_TYPE_DEDICATED == enBearerCntxtType )
    {
        vos_printf("%-30s : %s\r\n","承载类型","专有承载");
    }
    else
    {
        vos_printf("%-30s : %s\r\n","承载类型","缺省承载");
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_ShowSdfBearerType
 Description     : 打印承载类型
 Input           : enBearerCntxtType-----------承载类型
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-12-21  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_ShowSdfBearerType(APP_ESM_BEARER_TYPE_ENUM_UINT32 enBearerCntxtType)
{
    if(APP_ESM_BEARER_TYPE_DEDICATED == enBearerCntxtType )
    {
        vos_printf("%-30s : %s\r\n","承载类型","专有承载");
    }
    else
    {
        vos_printf("%-30s : %s\r\n","承载类型","缺省承载");
    }
}


/*****************************************************************************
 Function Name   : NAS_ESM_ShowPti
 Description     : 打印PTI
 Input           : pstStateTbl
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-1-19  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_ShowPti(const NAS_ESM_STATE_INFO_STRU *pstStateTbl)
{
    if (NAS_ESM_OP_TRUE == pstStateTbl->bitOpNwMsgRecord)
    {
        vos_printf("%-30s : %d\r\n","PTI值",pstStateTbl->stNwMsgRecord.ucPti);
    }
}


VOS_VOID NAS_ESM_ShowProcedureState
(
    NAS_ESM_PROC_TRANS_STATE_ENUM_UINT8 enProcTransTState
)
{
    if(NAS_ESM_BEARER_PROC_TRANS_STATE_PENDING == enProcTransTState )
    {
        vos_printf("%-30s : %s\r\n","procedure状态","pending态");
    }
    else
    {
        vos_printf("%-30s : %s\r\n","procedure状态","非激活态");
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_ShowIsWaitForUserAnswer
 Description     : 打印是否处于等待用户回复
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-1-19  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_ShowIsWaitForUserAnswer( VOS_UINT8 ucIsWaitForUserAnswer )
{
    if (PS_TRUE == ucIsWaitForUserAnswer)
    {
        vos_printf("%-30s : %s\r\n","是否处于等待用户回复", "是");
    }
    else
    {
        vos_printf("%-30s : %s\r\n","是否处于等待用户回复", "否");
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_ShowHasDedecodedNwMsg
 Description     : 打印是否存在译码后的网络消息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-1-19  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_ShowHasDedecodedNwMsg
(
    const NAS_ESM_NW_MSG_STRU          *pstDecodedNwMsg
)
{
    if (VOS_NULL_PTR != pstDecodedNwMsg)
    {
        vos_printf("%-30s : %s\r\n","是否存在译码后的网络消息", "是");
    }
    else
    {
        vos_printf("%-30s : %s\r\n","是否存在译码后的网络消息", "否");
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_ShowTimerInfo
 Description     : 打印定时器信息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-1-19  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_ShowTimerInfo
(
    const NAS_ESM_TIMER_STRU           *pstTimerInfo
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulStateTimerNum;

    ulStateTimerNum = sizeof(g_astEsmTimerArray)/sizeof(NAS_ESM_TIMER_PRINT_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulStateTimerNum; ulLoop++)
    {
        if (g_astEsmTimerArray[ulLoop].ulTimerId == pstTimerInfo->enPara)
        {
            break;
        }
    }

    if ( ulLoop < ulStateTimerNum )
    {
        vos_printf("%-30s\r\n",g_astEsmTimerArray[ulLoop].aucPrintString);
    }
    else
    {
        vos_printf("当前没有启动定时器\r\n");
        return;
    }

    if (VOS_NULL_PTR != pstTimerInfo->hTimer)
    {
        vos_printf("%-30s : %s\r\n","开启状态","开启");
    }
    else
    {
        vos_printf("%-30s : %s\r\n","开启状态","关闭");
    }

    vos_printf("%-30s : %d\r\n","超时次数",pstTimerInfo->ucExpireTimes);

}


VOS_VOID  NAS_ESM_ShowCommonInfo( )
{
    NAS_ESM_BUFF_MANAGE_INFO_STRU      *pstEsmBuffManInfo   = NAS_ESM_GetEsmBufferManageInfoAddr();

    vos_printf("\r\n");

    /* 打印注册状态 */
    NAS_ESM_ShowRegisterStatus();

    /* 打印PDN连接数目 */
    if (NAS_ESM_PS_REGISTER_STATUS_ATTACHED == NAS_ESM_GetEmmStatus())
    {
        vos_printf("%-30s : %d\r\n","UE的PDN连接数量",pg_stNasEsmEntity->ulCurPdnConNum);
    }

    /* 打印承载管理方式 */
    NAS_ESM_ShowBearerManagementType();

    /* 打印UE的IP地址 */
    NAS_ESM_ShowUeIp();

    /* 打印ESM缓存记录数 */
    vos_printf("%-30s : %d\r\n","ESM ATTACHING类型缓存记录数",pstEsmBuffManInfo->ucAttBuffItemNum);
    vos_printf("%-30s : %d\r\n","ESM PTI类型缓存记录数",pstEsmBuffManInfo->ucPtiBuffItemNum);

    vos_printf("\r\n");
}
VOS_VOID Nas_ESM_ShowAllSdfDynamicInfo(  )
{
    NAS_ESM_SDF_CNTXT_INFO_STRU              *pstSdfInfo = VOS_NULL_PTR;
    VOS_UINT32                                ulCid = NAS_ESM_NULL;
    VOS_UINT32                                ulEpsbId = NAS_ESM_NULL;
    VOS_UINT32                                ulSdfCount = NAS_ESM_NULL;
    VOS_UINT32                                ulSdfIndex = NAS_ESM_NULL;

    for ( ulCid = NAS_ESM_MIN_CID; ulCid <= NAS_ESM_MAX_CID; ulCid++ )
    {
        pstSdfInfo = NAS_ESM_GetSdfCntxtInfo(ulCid);

        ulEpsbId = pstSdfInfo->ulEpsbId;

        if ((NAS_ESM_MIN_EPSB_ID <= ulEpsbId) && (NAS_ESM_MAX_EPSB_ID >= ulEpsbId))
        {
            ulSdfCount++;
        }
    }

    vos_printf("\r\n");
    vos_printf("%-30s : %d\r\n","ESM保存的SDF数量",ulSdfCount);
    vos_printf("\r\n");

    for ( ulCid = NAS_ESM_MIN_CID ; ulCid <= NAS_ESM_MAX_CID; ulCid++ )
    {
        pstSdfInfo = NAS_ESM_GetSdfCntxtInfo(ulCid);

        ulEpsbId = pstSdfInfo->ulEpsbId;

        if ((NAS_ESM_MIN_EPSB_ID <= ulEpsbId) && (NAS_ESM_MAX_EPSB_ID >= ulEpsbId))
        {
            vos_printf("第%d个SDF的信息如下\r\n",(++ulSdfIndex));

            vos_printf("%-30s : %d\r\n","该SDF对应的CID",ulCid);
            vos_printf("%-30s : %d\r\n","该SDF对应的EpsbId",pstSdfInfo->ulEpsbId);
            vos_printf("%-30s : %d\r\n","该SDF的Packetfilter个数",pstSdfInfo->ulSdfPfNum);

            NAS_ESM_ShowTft(pstSdfInfo->ulSdfPfNum, pstSdfInfo->astSdfPfInfo);

            vos_printf("\r\n");
        }
    }

}


VOS_VOID  NAS_ESM_ShowSdfDynamicInfo( VOS_UINT32 ulCid )
{
    NAS_ESM_SDF_CNTXT_INFO_STRU              *pstSdfInfo = VOS_NULL_PTR;
    VOS_UINT32                                ulSdfPfNum = NAS_ESM_NULL;

    vos_printf("\r\n");

    if (NAS_ESM_MAX_CID < ulCid)
    {
        vos_printf("输入的CID值错误－CID取值范围为0..31 \r\n");
        return;
    }

    pstSdfInfo = NAS_ESM_GetSdfCntxtInfo(ulCid);

    vos_printf("*******************CID为%d的SDF的动态信息如下******************\r\n",ulCid);
    vos_printf("%-30s : %d\r\n","该SDF对应的EpsbId",pstSdfInfo->ulEpsbId);
    vos_printf("\r\n");

    NAS_ESM_ShowQos(&pstSdfInfo->stSdfQosInfo.stQosInfo);
    vos_printf("\r\n");

    ulSdfPfNum = pstSdfInfo->ulSdfPfNum;

    if ( NAS_ESM_NULL == ulSdfPfNum)
    {
        vos_printf("输入的CID不存在TFT信息!\r\n");
        vos_printf("\r\n");
        return;
    }
    else
    {
        vos_printf("该SDF对应TFT信息如下\r\n");
        NAS_ESM_ShowTft(pstSdfInfo->ulSdfPfNum, pstSdfInfo->astSdfPfInfo);
        vos_printf("\r\n");
    }

    vos_printf("\r\n");
}

VOS_VOID NAS_ESM_ShowPCO(const NAS_ESM_EPSB_CNTXT_INFO_STRU *pstEpsbInfo)
{
    VOS_UINT8        ulCnt = NAS_ESM_NULL;

    if ((PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(pstEpsbInfo->enBearerCntxtType))
        && (NAS_ESM_OP_TRUE == pstEpsbInfo->bitOpPco))
    {

        vos_printf("该承载存在PCO,PCO信息如下:\r\n");
        vos_printf("%-30s : %d\r\n","IPv4 DNS服务器数量      ",pstEpsbInfo->stPcoInfo.ucIpv4DnsSerNum);

        for (ulCnt = 0; ulCnt < pstEpsbInfo->stPcoInfo.ucIpv4DnsSerNum; ulCnt++)
        {
            vos_printf("第%d个IPv4 DNS的IP地址                    : %d.%d.%d.%d\r\n",
                ulCnt + 1,
                pstEpsbInfo->stPcoInfo.astIpv4DnsServer[ulCnt].aucIpV4Addr[0],
                pstEpsbInfo->stPcoInfo.astIpv4DnsServer[ulCnt].aucIpV4Addr[1],
                pstEpsbInfo->stPcoInfo.astIpv4DnsServer[ulCnt].aucIpV4Addr[2],
                pstEpsbInfo->stPcoInfo.astIpv4DnsServer[ulCnt].aucIpV4Addr[3]);
        }

        vos_printf("%-30s : %d\r\n","IPv6 DNS服务器数量      ",pstEpsbInfo->stPcoInfo.ucIpv6DnsSerNum);

        for (ulCnt = 0; ulCnt < pstEpsbInfo->stPcoInfo.ucIpv6DnsSerNum; ulCnt++)
        {
            vos_printf("第%d个IPv6 DNS的IP地址                    : %d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d\r\n", ulCnt + 1,
                pstEpsbInfo->stPcoInfo.astIpv6DnsServer[ulCnt].aucIpV6Addr[0],
                pstEpsbInfo->stPcoInfo.astIpv6DnsServer[ulCnt].aucIpV6Addr[1],
                pstEpsbInfo->stPcoInfo.astIpv6DnsServer[ulCnt].aucIpV6Addr[2],
                pstEpsbInfo->stPcoInfo.astIpv6DnsServer[ulCnt].aucIpV6Addr[3],
                pstEpsbInfo->stPcoInfo.astIpv6DnsServer[ulCnt].aucIpV6Addr[4],
                pstEpsbInfo->stPcoInfo.astIpv6DnsServer[ulCnt].aucIpV6Addr[5],
                pstEpsbInfo->stPcoInfo.astIpv6DnsServer[ulCnt].aucIpV6Addr[6],
                pstEpsbInfo->stPcoInfo.astIpv6DnsServer[ulCnt].aucIpV6Addr[7],
                pstEpsbInfo->stPcoInfo.astIpv6DnsServer[ulCnt].aucIpV6Addr[8],
                pstEpsbInfo->stPcoInfo.astIpv6DnsServer[ulCnt].aucIpV6Addr[9],
                pstEpsbInfo->stPcoInfo.astIpv6DnsServer[ulCnt].aucIpV6Addr[10],
                pstEpsbInfo->stPcoInfo.astIpv6DnsServer[ulCnt].aucIpV6Addr[11],
                pstEpsbInfo->stPcoInfo.astIpv6DnsServer[ulCnt].aucIpV6Addr[12],
                pstEpsbInfo->stPcoInfo.astIpv6DnsServer[ulCnt].aucIpV6Addr[13],
                pstEpsbInfo->stPcoInfo.astIpv6DnsServer[ulCnt].aucIpV6Addr[14],
                pstEpsbInfo->stPcoInfo.astIpv6DnsServer[ulCnt].aucIpV6Addr[15]);
        }

    }
    else
    {
        vos_printf("该承载不存在PCO信息\r\n");
    }

}

VOS_VOID NAS_ESM_ShowEpsbInfo(VOS_UINT32 ulEpsbId)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbInfo         = VOS_NULL_PTR;

    vos_printf("\r\n");

    if ((ulEpsbId < NAS_ESM_MIN_EPSB_ID) || (ulEpsbId > NAS_ESM_MAX_EPSB_ID))
    {
        vos_printf("输入的EPSBID值错误－EPSBID取值范围为5..15 \r\n");
        return;
    }

    pstEpsbInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    vos_printf("*******************EPS承载%d的相关信息如下******************\r\n",ulEpsbId);

    /* 打印承载状态 */
    NAS_ESM_ShowBearerState(pstEpsbInfo->enBearerCntxtState);
    vos_printf("\r\n");

    /* 打印承载类型 */
    NAS_ESM_ShowBearerType(pstEpsbInfo->enBearerCntxtType);
    vos_printf("\r\n");

    /* 打印关联缺省承载号 */
    NAS_ESM_ShowLinkEpsbId(pstEpsbInfo->ulLinkedEpsbId);
    vos_printf("\r\n");

    /* 打印承载QOS信息 */
    NAS_ESM_ShowEpsQos(pstEpsbInfo);
    vos_printf("\r\n");

    /* 打印承载包含的SDF ID */
    NAS_ESM_ShowEpsSdfId(pstEpsbInfo);
    vos_printf("\r\n");

    /* 打印PDN信息 */
    NAS_ESM_ShowEpsPdn(pstEpsbInfo);
    vos_printf("\r\n");

    /* 打印APN信息 */
    NAS_ESM_ShowEpsApn(pstEpsbInfo);
    vos_printf("\r\n");

    /* 打印APN-AMBR信息 */
    NAS_ESM_ShowEpsApnAmbr(pstEpsbInfo);

    /* 打印PCO信息 */
    NAS_ESM_ShowPCO(pstEpsbInfo);
}

/*****************************************************************************
 Function Name   : NAS_ESM_ShowAllEpsbInfo
 Description     : 打印所有承载信息，包括激活的和未激活的
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-1-18  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_ShowAllEpsbInfo( VOS_VOID )
{
    VOS_UINT32                 ulEpsbId;

    for ( ulEpsbId = NAS_ESM_MIN_EPSB_ID; ulEpsbId <= NAS_ESM_MAX_EPSB_ID; ulEpsbId++ )
    {
        /* 显示承载信息 */
        NAS_ESM_ShowEpsbInfo(ulEpsbId);
    }
}
VOS_VOID  NAS_ESM_ShowAllActiveEpsbInfo( VOS_VOID )
{
    VOS_UINT32                 ulEpsbId;
    VOS_UINT32                 ulActiveNum = NAS_ESM_NULL;

    for ( ulEpsbId = NAS_ESM_MIN_EPSB_ID; ulEpsbId <= NAS_ESM_MAX_EPSB_ID; ulEpsbId++ )
    {
        if ( NAS_ESM_BEARER_STATE_INACTIVE == NAS_ESM_GetBearCntxtState(ulEpsbId))
        {
            continue;
        }
        else
        {
            ulActiveNum++;

            /* 显示承载信息 */
            NAS_ESM_ShowEpsbInfo(ulEpsbId);
        }
    }

    if ( NAS_ESM_NULL == ulActiveNum )
    {
        vos_printf("%-30s\r\n","当前不存在激活的EPS承载");
    }
}
/*lint +e960*/

VOS_VOID NAS_ESM_ShowSdfStaticInfo( VOS_UINT32 ulCid )
{
    NAS_ESM_SDF_PARA_STRU  *pstSdfPara  = VOS_NULL_PTR;

    vos_printf("\r\n");

    if (NAS_ESM_MAX_UE_CONTRUL_CID < ulCid)
    {
        vos_printf("输入的CID值错误－CID取值范围为0..31 \r\n");
        return;
    }

    vos_printf("*******************CID %d的相关信息如下********************\r\n",ulCid);

    /*获取本地结构指针*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

    /* 打印关联CID */
    NAS_ESM_ShowLinkCid(pstSdfPara);
    vos_printf("\r\n");

    /* 打印承载类型 */
    NAS_ESM_ShowSdfBearerType(pstSdfPara->enBearerCntxtType);
    vos_printf("\r\n");

    /* 打印QOS信息 */
    NAS_ESM_ShowCidInfoQos(pstSdfPara);
    vos_printf("\r\n");

    /* 打印TFT信息 */
    NAS_ESM_ShowTft(pstSdfPara->ulPfNum, pstSdfPara->astCntxtTftInfo);
    vos_printf("\r\n");

    /* 打印PND类型 */
    NAS_ESM_ShowPdnTpe(pstSdfPara);
    vos_printf("\r\n");

    /* 打印APN信息 */
    NAS_ESM_ShowCidInfoApn(pstSdfPara);
    vos_printf("\r\n");

    /* 打印IP信息获取方式 */
    NAS_ESM_ShowIpAllocType(pstSdfPara);
    vos_printf("\r\n");

    vos_printf("cid in static sdf info: %d", pstSdfPara->ulCId);

    vos_printf("\r\n");
}


VOS_VOID Nas_ESM_ShowAllSdfStaticInfo(  )
{
    VOS_UINT32 ulCid;

    vos_printf("\r\n");

    vos_printf("******************CID 0-11 的相关信息如下*******************\r\n");

    for ( ulCid = NAS_ESM_MIN_CID; ulCid <= 10; ulCid++ )
    {
        NAS_ESM_ShowSdfStaticInfo(ulCid);
    }
}


VOS_VOID NAS_ESM_ShowStateTblInfo(  )
{
    VOS_UINT32                          ulStateTblIndex;
    VOS_UINT32                          uStateTablelFlag    = NAS_ESM_OP_FALSE;
    NAS_ESM_STATE_INFO_STRU             *pstStateTbl        = VOS_NULL_PTR;

    vos_printf("\r\n");

    for( ulStateTblIndex = 0; ulStateTblIndex < NAS_ESM_MAX_STATETBL_NUM; ulStateTblIndex++ )
    {
        pstStateTbl = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

        if (NAS_ESM_MAX_CID_NUM != pstStateTbl->ulCid)
        {
            uStateTablelFlag = NAS_ESM_OP_TRUE;

            vos_printf("*******************状态表%d的相关信息如下******************\r\n",ulStateTblIndex);
            vos_printf("%-30s : %d\r\n","cid值",pstStateTbl->ulCid);
            vos_printf("%-30s : %d\r\n","EPS承载ID",pstStateTbl->ulEpsbId);
            vos_printf("%-30s : %d\r\n","关联EPS承载ID",pstStateTbl->ulLinkedEpsbId);
            vos_printf("\r\n");

            /* 打印流程状态 */
            NAS_ESM_ShowProcedureState(pstStateTbl->enProcTransTState);

            /* 打印承载状态 */
            NAS_ESM_ShowBearerState(pstStateTbl->enBearerCntxtState);

            /* 打印承载类型 */
            NAS_ESM_ShowBearerType(pstStateTbl->enBearerCntxtType);

            /* 打印PTI */
            NAS_ESM_ShowPti(pstStateTbl);

            /* 打印是否处于等待用户回复 */
            NAS_ESM_ShowIsWaitForUserAnswer(pstStateTbl->ucIsWaitForUserAnswer);

            /* 打印是否存在译码后的网络信息 */
            NAS_ESM_ShowHasDedecodedNwMsg(pstStateTbl->pstDecodedNwMsg);

            /* 打印定时器信息 */
            NAS_ESM_ShowTimerInfo(&pstStateTbl->stTimerInfo);
            vos_printf("\r\n");

        }
    }

    if ( uStateTablelFlag == NAS_ESM_OP_FALSE )
    {
        vos_printf("%-30s\r\n","ESM当前不存在状态表信息");
    }
}
VOS_VOID  NAS_ESM_CmdHelp(  )
{
    vos_printf("\r\n");
    vos_printf("********************** NAS ESM 软调命令列表 *********************\r\n");
    vos_printf("%-30s : NAS ESM公共信息\r\n","NAS_ESM_ShowCommonInfo");
    vos_printf("%-30s : UE的所有SDF的静态信息\r\n","Nas_ESM_ShowAllSdfStaticInfo");
    vos_printf("%-30s : UE的某个SDF(0..31)的静态信息\r\n","NAS_ESM_ShowSdfStaticInfo(cid)");
    vos_printf("%-30s : UE的所有SDF的动态信息\r\n","Nas_ESM_ShowAllSdfDynamicInfo");
    vos_printf("%-30s : UE的某个SDF(0..31)的动态信息\r\n","NAS_ESM_ShowSdfDynamicInfo(cid)");
    vos_printf("%-30s : UE的所有EPS承载信息，包括激活和未激活\r\n","NAS_ESM_ShowAllEpsbInfo");
    vos_printf("%-30s : UE的所有激活EPS承载信息\r\n","NAS_ESM_ShowAllActiveEpsbInfo");
    vos_printf("%-30s : UE的某条EPS承载信息(5..15)\r\n","NAS_ESM_ShowEpsbInfo(epsid)");
    vos_printf("%-30s : ESM模块状态信息\r\n","NAS_ESM_ShowStateTblInfo");
    vos_printf("******************************************************************\r\n");
    vos_printf("\r\n");
}

/*****************************************************************************
 Function Name   : NAS
 Description     : NAS软调命令入口
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunbing49683      2010-4-20  Draft Enact

*****************************************************************************/
VOS_VOID NAS( NAS_OM_CMD_TYPE_ENUM_UINT8 enLayerName)
{
    switch ( enLayerName )
    {
        case NAS_OM_ALL :

            vos_printf("=====================UE NAS软调帮助命令==================\n");
            vos_printf("EMM模块软调信息请输入查询命令:     NAS 1\n");
            vos_printf("ESM模块软调信息请输入查询命令:     NAS 2\n");
            vos_printf("RABM模块软调信息请输入查询命令:    NAS 3\n");

            NAS_LMM_CmdHelp();
            NAS_ESM_CmdHelp();
            NAS_ERABM_CmdHelp();
            break;
        case NAS_OM_MM:
            NAS_LMM_CmdHelp();
            break;
        case NAS_OM_ESM:
            NAS_ESM_CmdHelp();
            break;
        case NAS_OM_RABM:
            NAS_ERABM_CmdHelp();
            break;
        default:
            break;
    }

    return;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

