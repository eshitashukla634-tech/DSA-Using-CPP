class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == NULL || head->next == NULL)
            return head;

        ListNode* newHead = head->next;
        ListNode* first = head;
        ListNode* second = head->next;
        ListNode* prev = NULL;

        while (first != NULL && second != NULL) {

            first->next = second->next;
            second->next = first;

            if (prev != NULL)
                prev->next = second;

            prev = first;

            first = first->next;

            if (first != NULL)
                second = first->next;
        }

        return newHead;
    }
};