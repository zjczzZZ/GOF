#include <iostream>

#include "BT.hpp"

namespace bt = BTree;

class SayHello : public bt::Node {
    Status update() override {
        std::cout << "Hello, World!" << std::endl;
        return Node::Status::Success;
    }
};

class SayYes : public bt::Node {
public:
    SayYes() {}
    SayYes(int i) { num = i; }
    Status update() override {
        std::cout << "Hello, Yes! " << num << std::endl;
        return Node::Status::Success;
    }

private:
    int num;
};

int main() {
    bt::BehaviorTree tree;

    auto repeater = std::make_shared<bt::Repeater>(5);
    repeater->setChild(std::make_shared<SayHello>());
    //   tree.setRoot(repeater);

    auto seq = std::make_shared<bt::Sequence>();
    seq->addChild(std::make_shared<SayYes>(1));
    seq->addChild(std::make_shared<SayYes>(2));
    seq->addChild(std::make_shared<SayYes>(3));

    tree.setRoot(seq);
    seq->addChild(repeater);
    // simulate 5 frames
    for (int i = 0; i < 5; i++)
        tree.update();

    return 0;
}