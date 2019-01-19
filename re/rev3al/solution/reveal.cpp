#include <iostream>
#include "pin.H"

UINT64 bblCount = 0;
ADDRINT main_low = 0;
ADDRINT main_high = 0;

VOID docount() {
    bblCount++;
}

VOID image(IMG img, VOID *v) {
    if (!IMG_IsMainExecutable(img))
        return;
    main_low = IMG_LowAddress(img);
    main_high = IMG_HighAddress(img);
}

VOID trace(TRACE trace, VOID *v) {
    ADDRINT trace_address = TRACE_Address(trace);
    if (trace_address >= main_low && trace_address <= main_high) {
        for (BBL bbl = TRACE_BblHead(trace); BBL_Valid(bbl); bbl = BBL_Next(bbl))
            BBL_InsertCall(bbl, IPOINT_BEFORE, (AFUNPTR)docount, IARG_UINT32, BBL_NumIns(bbl), IARG_END);
    }
}

VOID fini(INT32 code, VOID *v) {
    std::cerr << bblCount;
}

int main(int argc, char *argv[]) {
    PIN_Init(argc, argv);

    IMG_AddInstrumentFunction(image, 0);

    TRACE_AddInstrumentFunction(trace, 0);

    PIN_AddFiniFunction(fini, 0);

    PIN_StartProgram();

    return 0;
}
