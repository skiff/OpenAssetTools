Utils = {}

function Utils:include()
	includedirs {
		path.join(ProjectFolder(), "Utils")
	}
end

function Utils:link()
	links "Utils"
end

function Utils:use()
	
end

function Utils:project()
	local folder = ProjectFolder();

	project "Utils"
        targetdir(TargetDirectoryLib)
		location "%{wks.location}/src/%{prj.name}"
		kind "StaticLib"
		language "C++"
		
		files {
			path.join(folder, "Utils/**.h"), 
			path.join(folder, "Utils/**.cpp") 
		}
		
        vpaths {
			["*"] = {
				path.join(folder, "Utils")
			}
		}
		
        self:include()
end