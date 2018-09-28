#pragma once
#include "com_def.h"

enum traversing_type_t
{
    T_PREORDER = 0,
    T_MIDORDER = 1,
    T_POSTORDER = 2,
    T_LEVELORDER = 3,
};

struct BData
{
    BData(int _id = 0, const std::string& _name = "")
        : Id(_id)
        , name(_name)
    {}
    int Id = 0;
    std::string name = "";
};

struct BNode
{
    BData data;
    BNode(){}
    BNode(const BData& _data)
        : data(_data)
    {}

    ~BNode()
    {
        //printf("Del id:[%d],addr[%p]\n", data.Id, this);
        //std::cout << "Free: " << data.Id << std::endl;
    }

    BNode* p_left = nullptr;
    BNode* p_right = nullptr;
};

class BTree
{
private:
    BNode* m_pRoot = nullptr;
    int m_iSize = 0;
    int m_iMax = MAX_SIZE;
public:
    BTree(int max_size = MAX_SIZE)
        : m_iMax(max_size)
    {}

    ~BTree()
    {
        this->Destroy();
    }

    bool IsEmpty() const
    {
        return m_iSize <= 0;
    }
    bool IsFull() const
    {
        return m_iSize >= m_iMax;
    }

    bool AddItem(std::vector<BData>& data_vec)
    {
        for (auto& elem : data_vec)
        {
            if (!AddItem(elem))
                return false;
        }
        return true;
    }

    bool AddItem(const BData& data)
    {
        if (IsFull())
            return false;
        BNode* new_node = new BNode();
        if (!new_node)
            return false;
        new_node->data = data;
        this->Insert(new_node, m_pRoot);
        ++m_iSize;
        return true;
    }

    void Destroy()
    {
            this->FreeNode(m_pRoot);
    }

    void TraveringTree(int type = 0)
    {
        switch (type) {
        case T_PREORDER:
            PreorderTree(m_pRoot);
            break;
        case T_MIDORDER:
            MidorderTree(m_pRoot);
            break;
        case T_POSTORDER:
            PostorderTree(m_pRoot);
            break;
        case T_LEVELORDER:
            LevelorderTree(m_pRoot);
            break;
        default:
            break;
        }
    }

private:
    /*
     * 先序遍历，中左右
     * 中序遍历，左中右
     * 后序遍历，左右中
     * 层序遍历
    */
    void PreorderTree(const BNode* root)
    {
        if (root)
        {
            std::cout << root->data.Id << " ";
            PreorderTree(root->p_left);
            PreorderTree(root->p_right);
        }
    }

    void MidorderTree(const BNode* root)
    {
        if (root)
        {
            PreorderTree(root->p_left);
            std::cout << root->data.Id << " ";
            PreorderTree(root->p_right);
        }
    }

    void PostorderTree(const BNode* root)
    {
        if (root)
        {
            PreorderTree(root->p_left);
            PreorderTree(root->p_right);
            std::cout << root->data.Id << " ";
        }
    }

    void LevelorderTree(const BNode* root)
    {
        std::queue<const BNode*> q_nodes;
        q_nodes.push(root);
        while (!q_nodes.empty())
        {
            const BNode* out = q_nodes.front();
            q_nodes.pop();
            std::cout << out->data.Id << " ";
            if (out->p_left)
            {
                q_nodes.push(out->p_left);
            }
            if (out->p_right)
            {
                q_nodes.push(out->p_right);
            }
        }
    }

    // 这里参数为指针引用在函数调用结束后root指针也为空
    // 如果不是指针的引用，需要在调用结束后给root指针再次赋值null
    void FreeNode(BNode*& root)
    {
        if (root)
        {
            if (root->p_left)
            {
                    FreeNode(root->p_left);
            }
            if (root->p_right)
            {
                FreeNode(root->p_right);
            }
            SAVE_DELETE(root);
        }
    }

    void Insert(BNode* node, BNode*& root)
    {
        if (!root)
        {
            root = node;
            std::cout << " " << root->data.Id << std::endl;
            return;
        }

        if (root->data.Id > node->data.Id)
        {
            std::cout << "left: " << node->data.Id << std::endl;
            Insert(node, root->p_left);
        }
        else
        {
            std::cout << "right: " << node->data.Id << std::endl;
            Insert(node, root->p_right);
        }
    }
};
