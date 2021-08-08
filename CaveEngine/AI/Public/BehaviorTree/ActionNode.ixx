module;

#include <vector>

#include "BehaviorTreeNode.h"

export module ActionNode;

export namespace cave
{
    class ActionNode : public BehaviorTreeNode
    {
    public:
    public:
        ActionNode()
        {
            SetNodeName("");
            SetParentNode(NULL);
            SetTreeDepth(0);
            SetNodeFunction(NULL);
        }

        ActionNode(const char* nodeName, std::function<bool(GameObject&)> nodeFunction)
        {
            SetNodeName(nodeName);
            SetParentNode(NULL);
            SetTreeDepth(0);
            SetNodeFunction(nodeFunction);
        }

        ~ActionNode()
        {

        }

        virtual bool Run(GameObject& gameObject) override
        {
            return mNodeFunction(gameObject);
        }

        void SetNodeFunction(std::function<bool(GameObject&)> nodeFunction)
        {
            mNodeFunction = nodeFunction;
        }

        virtual void Clear() override
        {
            delete this;
        }

    private:
        std::function<bool(GameObject&)> mNodeFunction;

    
    };

}