{   "bin_fn"                    : "build/GluonicLQCD",
    "runName"                   : "B60_THERM_COLD",
    "N"                         : 24,
    "NT"                        : 48,
    "subDims"                   : [6, 6, 6, 6],
    "beta"                      : 6.0,
    "NCf"                       : 1,
    "NCor"                      : 600,
    "NTherm"                    : 25000,
    "NFlows"                    : 0,
    "NUpdates"                  : 30,
    "storeCfgs"                 : False,
    "storeThermCfgs"            : True,
    "verboseRun"                : False,
    "hotStart"                  : False,
    "RSTHotStart"               : False,
    "expFunc"                   : "morningstar", # options: luscher, taylor2, taylor4
    "observables"               : ["plaq","topc","energy"], # Optional: topologicalCharge, energyDensity
    "flowObservables"           : ["plaq","topc","energy"], # Optional: topologicalCharge, energyDensity
    "uTest"                     : False,
    "uTestVerbose"              : False,
    "SU3Eps"                    : 0.24,
    "flowEpsilon"               : 0.01,
    "metropolisSeed"            : 0,
    "randomMatrixSeed"          : 0,
    "threads"                   : 512,
    "cpu_approx_runtime_hr"     : 4,
    "cpu_approx_runtime_min"    : 30,
    "cpu_memory"                : 3800,
    "account_name"              : "nn2977k"}
