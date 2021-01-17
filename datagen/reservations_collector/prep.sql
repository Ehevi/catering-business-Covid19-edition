select r.reservation_id, ce.person_id from reservations r
inner join customers c
on r.customer_id=c.customer_id
inner join companies on c.customer_id=companies.customer_id
inner join companies_employees ce on companies.company_id=ce.company_id
order by reservation_id;