#include "worldmodel.ih"

void WorldModel::sayMessage(std::string message)
{
    rf<Predicate> sendMessage = new Predicate("", Predicate::type_list);
    rf<Predicate> pred = sendMessage->push(new Predicate("say"));

    pred->pushLeaf(message);

    d_comm.send(sendMessage);
    //    std::cerr << "WorldModel::sayMessage  I'll say " << message << std::endl;
}
