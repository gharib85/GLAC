{   "bin_fn"                    : "build/GluonicLQCD",
    "runName"                   : "prodRunBeta6_0",
    "N"                         : 24,
    "NT"                        : 48,
    "subDims"                   : [6, 6, 6, 6],
    "beta"                      : 6.0,
    "NCf"                       : 1000,
    "NCor"                      : 200,
    "NTherm"                    : 1000,
    "NFlows"                    : 1000,
    "NUpdates"                  : 10,
    "storeCfgs"                 : False,
    "storeThermCfgs"            : False,
    "verboseRun"                : False,
    "hotStart"                  : False,
    "expFunc"                   : "morningstar", # options: luscher, taylor2, taylor4
    "observables"               : ["plaq"], # Optional: topologicalCharge, energyDensity
    "flowObservables"           : ["plaq","topc","energy"], # Optional: topologicalCharge, energyDensity
    "uTest"                     : False,
    "uTestVerbose"              : False,
    "SU3Eps"                    : 0.24,
    "flowEpsilon"               : 0.01,
    "metropolisSeed"            : 0,
    "randomMatrixSeed"          : 0,
    "threads"                   : 512,
    "cpu_approx_runtime_hr"     : 24,
    "cpu_approx_runtime_min"    : 0,
    "cpu_memory"                : 3800,
    "account_name"              : "nn2977k"}