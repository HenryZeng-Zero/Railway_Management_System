add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate", {outputdir = ".vscode"})

add_requires("libadwaita-1","gobject-2.0","gio-2.0")

add_includedirs("gResource","src","rk-data","sqlite3")

target("gResource")
    set_kind("shared")
    set_languages("c11")
    set_optimize("fastest")
    add_files("gResource/**.c")
    add_packages("gio-2.0")

    before_build(function (target)
        local target_dir = path.join(os.projectdir(),"gResource")
        os.cd(target_dir)
        os.execv("make",{"clean"})
        os.execv("make")
    end)

target("rk-data")
    set_kind("shared")
    set_languages("c11")
    set_optimize("fastest")
    add_packages("gobject-2.0")
    add_files("rk-data/**.c")

target("sqlite3")
    set_kind("shared")
    set_languages("c11")
    set_optimize("fastest")
    set_warnings("none")
    add_files("sqlite3/**.c")

target("Railway_Management_System")
    set_kind("binary")
    set_languages("c11")
    set_optimize("fastest")

    add_packages("libadwaita-1")
    add_deps("rk-data","gResource")

    add_files("src/**.c")