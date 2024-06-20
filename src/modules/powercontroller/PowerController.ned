package simulator_5g_v2x.modules.powercontroller;


simple PowerController{
  parameters:
    string nicName;
    double coverDistance @unit(m) = default(0m);
    double desiredReceivedPower @unit(dBm);
}