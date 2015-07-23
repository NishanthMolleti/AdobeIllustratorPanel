#!/bin/sh
mkdir -p "${CONFIGURATION_BUILD_DIR}/${PRODUCT_NAME}.aip/Contents/Resources/png"
mkdir -p "${CONFIGURATION_BUILD_DIR}/${PRODUCT_NAME}.aip/Contents/Resources/txt"
cp -f "./Resource/raw/PL_Artboards_N.png" "${CONFIGURATION_BUILD_DIR}/${PRODUCT_NAME}.aip/Contents/Resources/png/PL_Artboards_N.png"
cp -f "./Resource/raw/PL_Artboards_N@2x.png" "${CONFIGURATION_BUILD_DIR}/${PRODUCT_NAME}.aip/Contents/Resources/png/PL_Artboards_N@2x.png"
cp -f "./Resource/raw/PL_Artboards_N@3to2x.png" "${CONFIGURATION_BUILD_DIR}/${PRODUCT_NAME}.aip/Contents/Resources/png/PL_Artboards_N@3to2x.png"
cp -f "./Resource/raw/IDToFile.txt" "${CONFIGURATION_BUILD_DIR}/${PRODUCT_NAME}.aip/Contents/Resources/txt/IDToFile.txt"

exit
