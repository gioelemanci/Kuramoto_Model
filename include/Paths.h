#ifndef PATHS_H
#define PATHS_H

#include <filesystem>
#include <string>
#include <iostream>

namespace km::paths {
    namespace fs = std::filesystem;

    // Directory principale dei dati analizzati
    static const fs::path root = fs::current_path() / "analysis_data";

    // Sottocartelle tematiche
    static const fs::path phasesDir = root / "phases";
    static const fs::path orderParamDir = root / "order_parameters";
    static const fs::path freqDir = root / "frequencies";
    static const fs::path lockedDir = root / "locked";
    static const fs::path driftingDir = root / "drifting";

    // Crea tutte le cartelle necessarie
    inline void ensureDirectoriesExist() {
        fs::create_directories(phasesDir);
        fs::create_directories(orderParamDir);
        fs::create_directories(freqDir);
        fs::create_directories(lockedDir);
        fs::create_directories(driftingDir);
    }

    // Restituisce il path completo per un file
    inline fs::path getFilePath(const fs::path& dir, const std::string& filename) {
        return dir / filename;
    }
}

#endif // PATHS_H