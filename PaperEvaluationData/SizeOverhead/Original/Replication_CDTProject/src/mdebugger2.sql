select count(*) from mdebugger.`clinetsrequest-refined`

insert into mdebugger.`clinetsrequest-refined`(
select 'keepalive' as msgtype , keepalive as resptime from mdebugger.refserver2keepalive )

delete from mdebugger.`clinetsrequest-refined` where msgtype='requestreply'

select * from mdebugger.`clients-refined1`
where messageid=2
insert   mdebugger.clinetsrequest  (select 'sendingmessage' as msgtype ,-sum(nano) as resptime  from mdebugger.`clients-refined1`
where messagetype="MessageSent" or messagetype="SendingMessage"
group by capsuleName,messageid)

update mdebugger.`clients-refined1` set nano=-nano where messagetype="MessageProcessed"
capsuleName="client4" where capsuleName="client"


select count(*) from     mdebugger.gdbMaindata
where msgtype='requestreply'