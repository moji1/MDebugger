create table mdebugger.refined  (
select 'RequestReply',RequestReply from mdebugger.refserver2RequestReply
union 
select 'RequestReply',RequestReply from mdebugger.refserver1RequestReply
union 
select 'keepalive',keepalive from mdebugger.refserver1keepalive 
)

Error Code: 1064. You have an error in your SQL syntax; 
check the manual that corresponds to your MySQL server
 version for the right syntax to use near 
 'union  select 'RequestReply',RequestReply from mdebugger.refserver1RequestReply ' at line 3
