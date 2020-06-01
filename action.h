#ifndef ACTION_H_
#define ACTION_H_

        void action_execute(int id, char key[S_SIZE], Vector *db);
        void action_list_all(Vector db);
        void action_list_by_name(char name[S_SIZE], Vector db);
        void action_add(char name[S_SIZE], Vector *db);
        void action_remove(char name[S_SIZE], Vector *db);
        void action_inc(char name[S_SIZE], Vector *db);

#endif