project "Tests"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "Source/**.h", "Source/**.cpp", "Source/**.cc" }
   
   includedirs
   {
      "../Core/Source",
      "../App/Source",
      "Source"
   }
   
   links
   {
      "Core",
      "gtest_main",
      "gtest", 
      "pthread", 
      "protobuf"
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:linux"
      links { "gtest", "pthread", "protobuf" }
      linkoptions { "-lgtest -pthread -lprotobuf" }

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"