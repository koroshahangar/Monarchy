## Event Reports
The following specifies how the report for each event handled by the WorldUpdater is to be structured.

### Environment Report
This is the first report which established the environment of the game.

> Env {MaxCount *max_count*}
  {Field *min_x* *max_x* *min_y* *max_y*}
  {Teams (Team *team_id* *team_name*)(Team *team_id* *team_name*)}
  {Agents (Player *unit_id* *team_id* *unit_type* *blood* *[position_x,position_y]*)(Player *unit_id* *team_id* *unit_type* *blood* *[position_x,position_y]*)}

### Invalid Move Report
This is reported when a player tries to make an invalid or illegal move and the server throws and exception. Player I

> Invalid *player_id*

### Spawn Report
This is reported when a leader spawns a new player into the game

> Spawn {(Player *unit_id* *team_id* *unit_type* *blood* *[position_x,position_y]*)} *leader_id*

### Walk Report
This is reported when a player moves to a new position

> Walk *[new_position_x,new_position_y]* *player_id*

### Attack Report
This is reported when a player attacks another player

> Attack *victim_id* *victim_new_blood_level* *attacker_id*

### Victory Report
This is reported when one of the teams win

> Victory *winner_team_id*

### Tie Report
This is reported when we reach maximum clock count of the game.

> Tie
