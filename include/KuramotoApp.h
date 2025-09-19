#ifndef KURAMOTOAPP_H
#define KURAMOTOAPP_H

#include <string>

namespace km {
    class Simulation;
}

class KuramotoApp {
public:
    void run(int argc, char* argv[]);
private:
    void saveAnalysis(const km::Simulation& sim, const std::string& suffix = "");
    void runGraphic();
    void runStepByStep();
    void runMultiCoupling();
    void runDefault();
    void promptUser();
};

#endif // KURAMOTOAPP_H