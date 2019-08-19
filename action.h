#ifndef ACTION_H_
#define ACTION_H_

        void action_execute(int id, char key[255], Vector *db);
        void action_list_all(Vector db);
        void action_list_by_name(char name[255], Vector db);
        void action_add(char name[255], Vector *db);
        void action_remove(char name[255], Vector *db);
        void action_inc(char name[255], Vector *db);

#endif