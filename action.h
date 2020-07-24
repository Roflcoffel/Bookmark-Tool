#ifndef ACTION_H_
#define ACTION_H_

        void action_execute(int id, char arg[S_SIZE], char format[S_SIZE], Vector *db, Vector backup_db);
        void action_list_all(Vector db);
        void action_list_by_name(char key[S_SIZE], char format[S_SIZE], Vector db);
        void action_add(char key_value[S_SIZE], Vector *db);
        void action_undo(Vector *db, Vector backup_db);
        int action_remove(char id[S_SIZE], Vector *db);
        int action_inc(char id[S_SIZE], Vector *db);
        int action_edit(char id_value[S_SIZE], Vector *db);
#endif