void mxp_enable()
{
    receive("<MXP negotiation enabled>\n");
}

void mxp_tag(string command)
{
    receive("<MXP TAG: " + command + ".>\n");
}

void act_mxp()
{
    efun::act_mxp();
}

void msp_enable()
{
    receive("<MSP negotiation: enabled.>\n");
}

void msdp_enable()
{
    receive("<MSDP negotiation: enabled.>\n");
}

void msdp(string req)
{
    receive("<MSDP request received.>\n");
    receive(req);
    receive("\n<MSDP request end.>\n");
}

void send_msdp_variable(string name, mixed value)
{
#if efun_defined(send_msdp_variable)
    efun::send_msdp_variable(name, value);
#else
    // FluffOS v2019 没有 send_msdp_variable efun；新版驱动会走上面分支
    receive("<当前驱动不支持 efun send_msdp_variable()>\n");
#endif
}

void zmp_enable()
{
    receive("<ZMP negotiation: enabled.>\n");
}

// 收到ZMP命令时调用
void zmp_command(string module, string *args)
{
    // todo
}

void send_zmp(string module, string *args)
{
    efun::send_zmp(module, args);
}
