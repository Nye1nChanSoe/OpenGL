workspace "LearnOpenGL"
	architecture "x64"
	configurations {
		"Debug",
		"Release"
	}
	language "C++"
	startproject ("OpenGLProj")

-- global var  Debug-x64 string
outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"
projectName = "OpenGLPlayground"

-- group the projects in the virtual folder called Dependencies
group("Dependencies")
	-- execute another lua script in the selected file path
	include (projectName.. "/vendor/GLFW")	
	include (projectName.. "/vendor/Glad")
group("")

project "OpenGLProj"
	location (projectName)  -- destination directory for a generated workspace or project file.
	kind "ConsoleApp"
	cppdialect "C++17"

	targetdir ("bin/" ..outputdir.. "/%{prj.name}")
	objdir ("bin-int/" ..outputdir.. "/%{prj.name}")

	files {
		projectName.. "/source/**.h",
		projectName.. "/source/**.cpp",
		projectName.. "/vendor/stb_image/stb_image.h",
		projectName.. "/vendor/stb_image/stb_image.cpp",
		projectName.. "/vendor/glm/**hpp",
		projectName.. "/vendor/glm/**inl"
	}

	includedirs {
		projectName.. "/source",
		projectName.. "/vendor/GLFW/include",
		projectName.. "/vendor/Glad/include",
		projectName.. "/vendor/glm",
		projectName.. "/vendor"
	}

	links {
		"opengl32.lib",
		"GLFW",
		"Glad"
	}

	defines {
		"GLFW_INCLUDE_NONE",		-- glfw will not include gl headers 
	}
