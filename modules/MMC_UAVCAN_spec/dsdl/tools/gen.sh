set -e

SCRIPT=$(readlink -f "$0")
SCRIPT_PATH=$(dirname "$SCRIPT")

LIBUAVCAN_PATH=${SCRIPT_PATH}/../../libuavcan
DSDL_GENERATOR_PATH=${LIBUAVCAN_PATH}/libuavcan/dsdl_compiler
UAVCAN_DSDL_PATH=${LIBUAVCAN_PATH}/dsdl/uavcan
CUSTOM_DSDL_PATH=${SCRIPT_PATH}/../src/mmc
GENERATED_PATH=${SCRIPT_PATH}/../generated

#echo "LIBUAVCAN_PATH: ${LIBUAVCAN_PATH}"
#echo "DSDL_GENERATOR_PATH: ${DSDL_GENERATOR_PATH}"
#echo "UAVCAN_DSDL_PATH: ${UAVCAN_DSDL_PATH}"
#echo "CUSTOM_DSDL_PATH: ${CUSTOM_DSDL_PATH}"
#echo "GENERATED_PATH: ${GENERATED_PATH}"

if [ ! -d "${LIBUAVCAN_PATH}" ]; then
echo "invalid LIBUAVCAN_PATH"
	exit 1
fi

if [ ! -d "${DSDL_GENERATOR_PATH}" ]; then
echo "invalid DSDL_GENERATOR_PATH"
	exit 1
fi

if [ ! -d "${UAVCAN_DSDL_PATH}" ]; then
echo "invalid UAVCAN_DSDL_PATH"
	exit 1
fi

if [ ! -d "${CUSTOM_DSDL_PATH}" ]; then
echo "invalid CUSTOM_DSDL_PATH"
	exit 1
fi

if [ ! -d "${GENERATED_PATH}" ]; then
	mkdir ${GENERATED_PATH}
fi

if [ ! -d "${GENERATED_PATH}" ]; then
echo "invalid GENERATED_PATH"
	exit 1
fi

rm ${GENERATED_PATH}/* -rf

${DSDL_GENERATOR_PATH}/./libuavcan_dsdlc --outdir ${GENERATED_PATH} --incdir ${UAVCAN_DSDL_PATH} ${CUSTOM_DSDL_PATH}

#echo "custom DSDL generated success"
exit 0
