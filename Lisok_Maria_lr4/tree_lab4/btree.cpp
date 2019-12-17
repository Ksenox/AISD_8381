#include "allheaders.h"
#include "btree.h"

struct Node* newNode(char v)
{
    struct Node *temp = new Node;
    temp->left = nullptr;
    temp->right = nullptr;
    temp->value = v;
    return temp;
};

string inorder(struct Node *root)
{
    if (!root)
            return "";
    string output;

    if (root->left || root->right)
        output += "(";

    output += inorder(root->left);
    output += root->value;
    output += inorder(root->right);

    if (root->left || root->right)
        output += ")";

    return output;
}

void calc(char value, Stack<char>& stack, vector<string>& steps, string& error){
    if(isOperation(value)){
        if(stack.isEmpty()){
            error += "check string. it must consist of numbers\n";
            return;
        }
        int sum = *stack.onTop()-'0';
        stack.pop();
        if (value=='+'){
            string str;
            str+=*stack.onTop();
            str += "+"+to_string(sum)+"=";
            sum+=(*stack.onTop()-'0');
            str+=to_string(sum);
            steps.push_back(str);
        }

        if (value=='-'){
            string str;
            str+=*stack.onTop();
            str += "-"+to_string(sum)+"=";
            sum =(*stack.onTop()-'0')-sum;
            str+=to_string(sum);
            steps.push_back(str);
        }

        if (value=='*'){
            string str;
            str+=*stack.onTop();
            str += "*"+to_string(sum)+"=";
            sum*=(*stack.onTop()-'0');
            str+=to_string(sum);
            steps.push_back(str);
        }
        stack.pop();
        stack.push(static_cast<char>(sum + '0'));
    }else{
        if(!isdigit(value)){
                error += "check string. it must consist of numbers\n";
                return;
        }
        stack.push(value);
    }
}

void postorder(struct Node *t, Stack<char>& stack, vector<string>& steps, string & errors)
{
    if(t){
        postorder(t->left, stack, steps,errors);
        postorder(t->right, stack, steps, errors);
        if(errors.empty())
            calc(t->value, stack, steps, errors);
    }else{
        return;
    }
}

void simplifying(string & str) {
    cout << str << endl;
    if(!str.compare("(1+0)")|| !str.compare("(1-0)") || !str.compare("(0+1)")){
        str = "1";
        return;
    }
    else if(!str.compare("(0+0)")){
        str = "0";
        return;
    }
    else if(!str.compare("(1+1)")){
        str = "2";
        return;
    }
    smatch resStr;

    regex reg1("\\((.*)[+-]0\\)");
    if(regex_match(str, resStr, reg1)){
        str = resStr[1] ;
    }

    regex reg2("\\(0\\+(.*)\\)");
    if(regex_match(str, resStr, reg2)){
        str = resStr[1] ;
    }

    regex reg3("\\((.*)\\*1\\)");
    if(regex_match(str, resStr, reg3)){
        str = resStr[1];
    }

    regex reg4("\\((.*)\\*0\\)");
    if(regex_match(str, resStr, reg4)){
        str = "0";
        return;
    }

    regex reg5("\\(0\\*(.*)\\)");
    if(regex_match(str, resStr, reg5)){
        str = "0";
        return;
    }


    regex reg6("\\((.*)-(.*)\\)");
    if(regex_match(str, resStr, reg6) && !resStr[1].compare(resStr[2])) {
        str = "0";
        return;
    }

    regex reg8("\\(([a-z]\\*){1,}([a-z]\\*[a-z]\\*)*([0-9]+\\*)[a-z]{1,}(\\*[a-z])*\\)");
    string temp = str;
    if(regex_search(str, resStr, reg8)) {
            temp.erase(str.find(resStr[3]), static_cast<unsigned long>(resStr[3].length()));
            temp.insert(str.find(resStr[0]), resStr[3]);
            str = temp;
            cout << "reg8";
    }

    regex reg9("\\(([0-9]*)\\*?\\((.*)\\)([+-])([0-9]*)\\*?\\((.*)\\)\\)");
    if(regex_search(str, resStr, reg9)) {
        if(!resStr[2].compare(resStr[5])) {
            int factor1=1, factor2=1;
            if(resStr[1].length()) {
                 factor1 = stoi(resStr[1]);
            }
            if(resStr[4].length()) {
                 factor2 = stoi(resStr[4]);
            }
            if(resStr[3]=="+") {
                factor1 += factor2;
            }else{
                factor1 -= factor2;
            }
            string buf = to_string(factor1)+"*";
            if(resStr[2].length()>1){
                buf += "(";
                buf += resStr[2];
                buf += ")";
            }
            str = buf;
        }
        return;
    }

    regex reg10("\\(([0-9]*)([+-*])([0-9]*)\\)");
    if(regex_match(str, resStr, reg10)) {
        int factor1, factor2;
        factor1 = stoi(resStr[1]);
        factor2 = stoi(resStr[3]);
        if(resStr[2]=="+") {
            factor1 += factor2;
        }else if(resStr[2]=="-"){
            factor1 -= factor2;
        }else if(resStr[2]=="*"){
            factor1 *= factor2;
        }

        str = to_string(factor1);
        return;
    }

    regex reg7("\\((.*)\\+(.*)\\)");
    if(regex_match(str, resStr, reg7) && !resStr[1].compare(resStr[2])) {
        string result = "2*";
        result += resStr[1];
        str = result;
        return;
    }

}

string Diff (struct Node *root, char var)
{
    if (!root)
        return "";
    if (root->value) {
        if (root->value == var)
            return "1";
        else if(root->value == '+'){
            string str = "(" + Diff(root->left, var) + "+" + Diff(root->right, var) + ")";
            simplifying(str);
            return str;
        }
        else if(root->value == '-'){
            string str = "(" + Diff(root->left, var) + "-" + Diff(root->right, var) + ")";
            simplifying(str);
            return str;
        }
        else if(root->value == '*'){
            string str1 = inorder(root->left);
            if(str1.length()!=1){
                //str1 = "("+str1+")";
                simplifying(str1);
            }

            string str2= inorder(root->right);
            if(str2.length()!=1){
                //str2 = "("+str2+")";
                simplifying(str2);
            }

            string str3 = Diff(root->right, var);
            string arg1 = "("+str1+"*"+str3+")";
            simplifying(arg1);
            string str4 =  Diff(root->left, var);
            string arg2 = "("+str2+"*"+str4+")";
            simplifying(arg2);
            string result = "("+arg1+"+"+arg2+")";
            simplifying(result);
            return result;
        }else
            return "0";
    }

    return "0";
}

int countDeep(struct Node *&node) {
    if (node == nullptr)
        return 0;
    int cl = countDeep(node->left);
    int cr = countDeep(node->right);
    return 1 + ((cl>cr)?cl:cr);
}

int eval(struct Node* root, string & err) {

    if (!root)
        return 0;

    if (!root->left && !root->right){
        if(isdigit(root->value))
            return root->value - '0';
        err = "Input numbers!";
        return 0;
    }


    int l_val = eval(root->left, err);


    int r_val = eval(root->right, err);


    if (root->value=='+')
        return l_val+r_val;

    if (root->value=='-')
        return l_val-r_val;

    if (root->value=='*')
        return l_val*r_val;

    return 0;
}

struct Node* constructTree(string & postfix) {
    Stack<struct Node *> st;
    struct Node *t, *t1, *t2;

    for (unsigned long i=0; i<postfix.length(); i++)
    {

        if (!isOperation(postfix[i]))
        {
            t = newNode(postfix[i]);
            st.push(t);
        }
        else
        {
            t = newNode(postfix[i]);
            t1 = *st.onTop();
            st.pop();
            t2 = *st.onTop();
            st.pop();
            t->left = t1;
            t->right = t2;
            st.push(t);
        }
    }
    t = *st.onTop();
    st.pop();

    return t;
}

