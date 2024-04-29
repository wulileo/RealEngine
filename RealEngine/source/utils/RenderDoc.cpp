#include "RenderDoc.h"

#include <Windows.h>
#include <iostream>

RENDERDOC_API_1_4_1 *RenderDoc::rdoc_api = nullptr;

void RenderDoc::init() {
    HMODULE mod = LoadLibraryA("renderdoc.dll");
    if (mod) {
        auto API = (pRENDERDOC_GetAPI) GetProcAddress(mod, "RENDERDOC_GetAPI");
        int ret = API(eRENDERDOC_API_Version_1_4_1, (void **) &rdoc_api);
        if (ret == 0) {
            printf("RenderDoc API loaded successfully\n");
        } else {
            printf("Failed to load RenderDoc API\n");
        }
    } else {
        printf("Failed to load renderdoc.dll\n");
    }
}

void RenderDoc::start() {
    rdoc_api->StartFrameCapture(nullptr, nullptr);
}

void RenderDoc::end() {
    rdoc_api->EndFrameCapture(nullptr, nullptr);
}
