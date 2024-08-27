add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate", {outputdir = ".vscode"})

add_requires("libadwaita-1","gobject-2.0")

rule("ResCopy")
    after_build(function (target)
        function ResCopy(name) 
            local proj_dir = os.projectdir()
            local source_design_path = path.join(proj_dir,name)
            local target_dir = path.join(proj_dir,target:targetdir())
            local target_design_path = path.join(target_dir,name)
            
            if os.isdir(target_design_path) then
                os.rm(target_design_path)
                os.cp(source_design_path,target_design_path)
            else 
                os.cp(source_design_path,target_design_path)
                print()
            end
            cprint("=> 同步" .. name .. " 资源目录 ${bright green}✓${clear}")
        end
        
        ResCopy("design")

    end)

target("rk-data")
    set_kind("static")
    set_languages("c11")
    set_optimize("fastest")
    add_packages("gobject-2.0")
    add_includedirs("rk-data")
    add_files("rk-data/**.c")

target("Railway_Management_System")
    set_kind("binary")
    set_languages("c11")
    set_optimize("fastest")
    add_rules("ResCopy")

    add_packages("libadwaita-1")
    add_deps("rk-data")
    
    add_includedirs("src","rk-data")
    add_files("src/**.c")