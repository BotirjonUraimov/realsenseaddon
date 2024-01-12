{
  "targets": [
    {
      "target_name": "realsense_addon",
      "sources": [ "src/realsense_addon.cpp" ],
      "include_dirs": [   
          "C:/Program Files (x86)/Intel RealSense SDK 2.0/include", 
           "<!@(node -p \"require('node-addon-api').include\")",
            "<!@(node -p \"require('node-addon-api').path\")",
          "<!(node -e \"require('nan')\")"
    ],
     "libraries": [
        "C:/Program Files (x86)/Intel RealSense SDK 2.0/lib/x64/realsense2.lib",
      ],
    }
  ]
}
