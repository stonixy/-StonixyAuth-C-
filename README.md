# StonixyAuth C++ Integration Guide

This example is designed for **Zero-Config** integration on Windows (Visual Studio).

## File Structure

To integrate StonixyAuth into your project, your folder structure should look like this:

```text
YourProject/
├── main.cpp               (Your source code)
└── stonixyauth/           (The StonixyAuth folder)
    ├── stonixyauth.hpp    (The main library)
    ├── json.hpp           (Download from nlohmann/json)
    ├── libcurl.lib        (Your compiled libcurl library)
    └── curl/              (Create this folder)
        ├── curl.h         (Put all curl headers here)
        ├── easy.h
        └── ...
```

## Dependencies

1.  **nlohmann/json**: Download `json.hpp` and place it directly inside the `stonixyauth/` folder.
2.  **libcurl**: 
    - Place `libcurl.lib` inside your project root or the `stonixyauth/` folder.
    - If you place it in a subfolder, you may need to add that folder to **Project Properties > VC++ Directories > Library Directories**.
    - If it's in the project root, the `#pragma comment` in `stonixyauth.hpp` will find it automatically.

## How to use

1.  Copy the `stonixyauth/` folder into your project.
2.  Include the library:
    ```cpp
    #include "stonixyauth/stonixyauth.hpp"
    ```
3.  Initialize the client and start authenticating!

## Troubleshooting Linker Errors

If you see `unresolved external symbol` errors:

1.  **Static vs DLL**: By default, `stonixyauth.hpp` assumes you are using a **Static Library**. If you are using a DLL version of curl, remove `#define CURL_STATICLIB` from the top of `stonixyauth.hpp`.
2.  **Library Path**: Ensure `libcurl.lib` is in the same folder as your `.vcxproj` file.
3.  **X86 vs X64**: Make sure your `libcurl.lib` matches your project architecture (e.g., don't use a 32-bit lib in a 64-bit project).
4.  **Additional Dependencies**: If your `libcurl.lib` was built with extra features (like Zlib), you will need those `.lib` files. 
    - **Fix 1**: Find `zlib.lib` in your curl download and put it next to `libcurl.lib`.
    - **Fix 2**: If you don't have it, open `stonixyauth.hpp` and comment out the line `#pragma comment(lib, "zlib.lib")`. Note: This may cause "unresolved external" errors if your libcurl requires it.
