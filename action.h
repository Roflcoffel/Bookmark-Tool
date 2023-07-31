#ifndef ACTION_H_
#define ACTION_H_

        void action_execute(int id, char arg[], char format[], Vector *db, Vector backup_db);
        void action_list_all(Vector db);
        void action_list_by_name(char key[], char format[], Vector db);
        void action_add(char key_value[], Vector *db);
        void action_undo(Vector *db, Vector backup_db);
        void action_inc_all(Vector *db);
        int action_remove(char id[], Vector *db);
        int action_inc(char id[], Vector *db);
        int action_edit(char id_value[], Vector *db);
#endif