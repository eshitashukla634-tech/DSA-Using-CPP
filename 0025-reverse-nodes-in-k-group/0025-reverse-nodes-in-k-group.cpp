class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode* prevGroup = &dummy;

        while (true) {
            ListNode* kth = prevGroup;

            for (int i = 0; i < k && kth != NULL; i++)
                kth = kth->next;

            if (kth == NULL)
                break;

            ListNode* nextGroup = kth->next;
            ListNode* prev = nextGroup;
            ListNode* curr = prevGroup->next;

            while (curr != nextGroup) {
                ListNode* next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
            }

            ListNode* oldFirst = prevGroup->next;
            prevGroup->next = kth;
            prevGroup = oldFirst;
        }

        return dummy.next;
    }
};