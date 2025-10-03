#include <cstdint>
#include <stdint.h>

/*
The Kernel Mode Driver (KMD) Communicates with the Micro Engine Scheduler (MES)
by submitting API commands to the MES queue ring buffer
thus our simulator must be compliant/implement the following
*/

// all apis have length of 64 DWORDS
enum { API_FRAME_SIZE_IN_DWORDS = 64 };

union MES_API_HEADER{
    struct{
        uint32_t type       :4;
        uint32_t opcode     :8;
        uint32_t dwsize     :8;
        uint32_t reserved   :12;
    };
    uint32_t u32All;
};

/* Indicates that the API request has been processed by the scheduler */
struct MES_API_STATUS{
    uint64_t api_completion_fence_addr;
    uint64_t api_completion_fence_value;
};

/* The following format applies to all APIs */
union MESAPI_APINAME{
    struct{
        union MES_API_HEADER header;
        struct MES_API_STATUS api_status;
        uint64_t timestamp;
    };
    uint32_t max_dwords_in_api[API_FRAME_SIZE_IN_DWORDS];
};

/* Opcodes define all supported MES APIs */
enum MES_SCH_API_OPCODE{
    MES_SCH_API_SET_HW_RSRC = 0,
    MES_SCH_API_SET_SCHEDULING_CONFIG = 1,
    MES_SCH_API_ADD_QUEUE = 2,
    MES_SCH_API_REMOVE_QUEUE = 3,
    MES_SCH_API_PERFORM_YIELD = 4,
    MES_SCH_API_SET_GANG_PRIORITY_LEVEL = 5,
    MES_SCH_API_SUSPEND = 6,
    MES_SCH_API_RESUME = 7,
    MES_SCH_API_RESET = 8,
    MES_SCH_API_SET_LOG_BUFFER = 9,
    MES_SCH_API_CHANGE_GANG_PRORITY = 10,
    MES_SCH_API_QUERY_SCHEDULER_STATUS = 11,
    MES_SCH_API_PROGRAM_GDS = 12,
    MES_SCH_API_SET_DEBUG_VMID = 13,
    MES_SCH_API_MISC = 14,
    MES_SCH_API_UPDATE_ROOT_PAGE_TABLE = 15,
    MES_SCH_API_AMD_LOG = 16,
    MES_SCH_API_SET_SE_MODE = 17,
    MES_SCH_API_SET_GANG_SUBMIT = 18,
    MES_SCH_API_MAX = 0xFF
};

/* Provides list of HW resources to be managed by the scheduler and configuration flags */
enum { MAX_COMPUTE_PIPES = 8 };
enum { MAX_GFX_PIPES = 2 };
enum { MAX_SDMA_PIPES = 2};

enum { MES_MAX_HWIP_SEGMENT = 12 };

enum MES_AMD_PRIORITY_LEVEL{
    AMD_PRIORITY_LEVEL_LOW = 0,
    AMD_PRIORITY_LEVEL_NORMAL = 1,
    AMD_PRIORITY_LEVEL_MEDIUM = 2,
    AMD_PRIORITY_LEVEL_HIGH = 3,
    AMD_PRIORITY_LEVEL_REALTIME = 4,

    AMD_PRIORITY_NUM_LEVELS
};

union MESAPI_SET_HW_RESOURCES{
    struct{
        union MES_API_HEADER header;
        uint32_t vmid_mask_mmhub;
        uint32_t paging_vmid;
        uint32_t compute_hqd_mask[MAX_COMPUTE_PIPES];
        uint32_t gfx_hqd_mask[MAX_GFX_PIPES];
        uint32_t sdma_hqd_mask[MAX_SDMA_PIPES];
        uint32_t aggregated_doorbells[AMD_PRIORITY_NUM_LEVELS];
        uint64_t g_sch_ctx_gpu_mc_ptr;
        uint64_t query_status_fence_gpu_mc_ptr;
        uint32_t gc_base[MES_MAX_HWIP_SEGMENT];
        uint32_t mmhub_base[MES_MAX_HWIP_SEGMENT];
        uint32_t osssys_base[MES_MAX_HWIP_SEGMENT];
        struct MES_API_STATUS api_status;
        union{  // Flags
            struct{
                uint32_t disable_reset : 1;
                uint32_t use_different_vmid_compute : 1;
                uint32_t disable_mes_log : 1;
                uint32_t apply_mmhub_pgvm_invalidate_ack_loss_wa : 1;
                uint32_t apply_grbm_remote_register_dummy_read_wa : 1;
                uint32_t second_gfx_pipe_enabled : 1;
                uint32_t enable_level_process_quantum_check : 1;
                uint32_t legacy_sch_mode : 1;
                uint32_t disable_add_queue_wptr_mc_addr : 1;
                uint32_t enable_mes_event_int_logging : 1;
                uint32_t enable_reg_active_poll : 1;
                uint32_t use_disable_queue_in_legacy_uq_preemption : 1;
                uint32_t send_write_data : 1;
                uint32_t os_tdr_timeout_override : 1;
                uint32_t use_rs64mem_for_proc_gang_ctx : 1;
                uint32_t use_add_queue_unmap_flag_addr : 1;
                uint32_t enable_mes_sch_stb_log : 1;
                uint32_t reserved : 15;
            };
            uint32_t uint32_all;
        };
        uint32_t oversubscription_timer;
        uint64_t doorbell_info;
        uint64_t event_intr_history_gpu_mc_ptr;
        uint64_t timestamp;
        uint32_t os_tdr_timeout_in_sec;
    };
    uint32_t max_dwords_in_api[API_FRAME_SIZE_IN_DWORDS];
};
