package simulator_5g_v2x.modules.dependencyGraph;

moduleinterface DependencyGraph {
    @display("i=block/network2,,0");
}

simple LeaderFollowerGraph like DependencyGraph {
    @display("i=block/network2,,0");
    @class("LeaderFollowerGraph");
}
