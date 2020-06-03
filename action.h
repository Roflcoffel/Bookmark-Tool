#ifndef ACTION_H_
#define ACTION_H_

        void action_execute(int id, char name[S_SIZE], bool arg_is_dirname, Vector *db);
        void action_list_all(Vector db);
        void action_list_by_name(char name[S_SIZE], Vector db);
        void action_add(char name[S_SIZE], Vector *db);
        void action_remove(char id[S_SIZE], Vector *db);
        void action_inc(char id[S_SIZE], Vector *db);

        void action_list_by_name_strict(char name[S_SIZE], Vector db);
        void action_list_by_name_ret_val_strict(char name[S_SIZE], Vector db);

#endif