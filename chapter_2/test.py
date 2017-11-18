import sys

upper_limits = [5, 9, 2, 5];
counter_vals = [0, 0, 0, 0];

#dynamic looper that returns 'True' when all iterations are complete
def increment_count():
     
     #iterate through all possibilites of a set
     update_parent = True;
     for idx in range(0, len(counter_vals)):
          rev_idx = (len(counter_vals)-1)-idx;
          
          if (not update_parent):
               break;
          
          counter_vals[rev_idx] = (1+counter_vals[rev_idx])%upper_limits[rev_idx];
          if (not counter_vals[rev_idx]):
               update_parent = True;
          else:
               update_parent = False;
               
     #inform user if all iterations are complete
     if (update_parent):
          return True;
     else:
          return False;
               
stop_loop = False;
while(not stop_loop):
     print(counter_vals);
     stop_loop = increment_count();