#define HAS_DEVICE_TREE 1

// FIXME
static const zbi_platform_id_t platform_id = {
    .vid = PDEV_VID_ARM,
    .pid = PDEV_PID_HIKEY960,
    .board_name = "raspberry Pi 3B",
};

static const zbi_cpu_config_t cpu_config = {
    .cluster_count = 1,
    .clusters = {
        {
            .cpu_count = 4,
        },
    },
};

static const zbi_mem_range_t mem_config[] = {
    {
        .type = ZBI_MEM_RANGE_RAM,
        .length = 0x80000000, // 1GB
    },
    {
        // memory to reserve to avoid stomping on bootloader data
        .type = ZBI_MEM_RANGE_RESERVED,
        .paddr = 0x00000000,
        .length = 0x00080000,
    },
};

static void append_board_boot_item(zbi_header_t* bootdata) {
    // add CPU configuration
    append_boot_item(bootdata, ZBI_TYPE_CPU_CONFIG, 0, &cpu_config,
                    sizeof(zbi_cpu_config_t) +
                    sizeof(zbi_cpu_cluster_t) * cpu_config.cluster_count);
    
    // add memory configuration
    append_boot_item(bootdata, ZBI_TYPE_MEM_CONFIG, 0, &mem_config,
                    sizeof(zbi_mem_range_t) * countof(mem_config));
}