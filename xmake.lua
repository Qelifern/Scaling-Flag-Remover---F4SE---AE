-- include subprojects
includes("lib/commonlibf4")

-- set project constants
set_project("scaling_flag_remover_ae")
set_version("1.0.1")
set_license("MIT")
set_languages("c++23")
set_warnings("allextra")

-- add common rules
add_rules("mode.debug", "mode.releasedbg")
add_rules("plugin.vsxmake.autoupdate")

-- define targets
target("scaling_flag_remover_ae")
    add_rules("commonlibf4.plugin", {
        name = "scaling_flag_remover_ae",
        author = "QELIFERN",
        description = "F4SE plugin using CommonLibF4"
    })

    -- add src files
    add_files("src/**.cpp")
    add_headerfiles("src/**.h")
    add_includedirs("src")
    set_pcxxheader("src/pch.h")
