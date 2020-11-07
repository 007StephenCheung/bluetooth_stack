#ifndef A2DP_SINK_H_H_H
#define A2DP_SINK_H_H_H
#include "bt_sdp.h"
#include "bt_avdtp.h"

typedef enum{
    AVDTP_SBC_48000 = 0x10,
    AVDTP_SBC_44100 = 0x20,
    AVDTP_SBC_32000 = 0x40,
    AVDTP_SBC_16000 = 0x80,
} sbc_sampling_frequency_t;

typedef enum{
    AVDTP_SBC_JOINT_STEREO  = 0x1,
    AVDTP_SBC_STEREO        = 0x2,
    AVDTP_SBC_DUAL_CHANNEL  = 0x4,
    AVDTP_SBC_MONO          = 0x8
} sbc_channel_mode_t;

typedef enum{
    AVDTP_SBC_BLOCK_LENGTH_16 = 0x10,
    AVDTP_SBC_BLOCK_LENGTH_12 = 0x20,
    AVDTP_SBC_BLOCK_LENGTH_8  = 0x40,
    AVDTP_SBC_BLOCK_LENGTH_4  = 0x80,
} sbc_block_length_t;

typedef enum{
    AVDTP_SBC_SUBBANDS_8 = 0x4,
    AVDTP_SBC_SUBBANDS_4 = 0x8,
} sbc_subbands_t;

typedef enum{
    AVDTP_SBC_ALLOCATION_METHOD_LOUDNESS = 1,
    AVDTP_SBC_ALLOCATION_METHOD_SNR      = 2,
} sbc_allocation_method_t;

struct a2dp_pcb_t
{
    struct a2dp_pcb_t *next; /* For the linked list */
	struct avdtp_pcb_t *avdtppcb;
	struct bd_addr_t remote_addr;
	uint8_t codec_type;
};

typedef struct
{
    void (*a2dp_sink_signal_connect_set_up)(struct bd_addr_t *remote_addr,uint8_t status);
    void (*a2dp_sink_signal_connect_realease)(struct bd_addr_t *remote_addr,uint8_t status);
    void (*a2dp_sink_stream_connect_set_up)(struct bd_addr_t *remote_addr,uint8_t status);
    void (*a2dp_sink_stream_connect_realease)(struct bd_addr_t *remote_addr,uint8_t status);
    void (*a2dp_sink_stream_start)(struct bd_addr_t *remote_addr,uint8_t value);
    void (*a2dp_sink_stream_realease)(struct bd_addr_t *remote_addr,uint8_t value);
    void (*a2dp_sink_stream_suspend)(struct bd_addr_t *remote_addr,uint8_t value);
    void (*a2dp_sink_stream_abort)(struct bd_addr_t *remote_addr,uint8_t value);
} a2dp_sink_cbs_t;



#define A2DP_PCB_REG(pcbs, npcb) do { \
                            npcb->next = *pcbs; \
                            *pcbs = npcb; \
                            } while(0)
#define A2DP_PCB_RMV(pcbs, npcb) do { \
                            if(*pcbs == npcb) { \
                               *pcbs = (*pcbs)->next; \
                            } else for(a2dp_sink_tmp_pcb = *pcbs; a2dp_sink_tmp_pcb != NULL; a2dp_sink_tmp_pcb = a2dp_sink_tmp_pcb->next) { \
                               if(a2dp_sink_tmp_pcb->next != NULL && a2dp_sink_tmp_pcb->next == npcb) { \
                                  a2dp_sink_tmp_pcb->next = npcb->next; \
                                  break; \
                               } \
                            } \
                            npcb->next = NULL; \
                            } while(0)


err_t a2dp_sink_init(a2dp_sink_cbs_t *cb);

#endif
