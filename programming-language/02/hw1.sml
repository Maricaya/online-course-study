fun is_older (((d1, m1, y1), (d2, m2, y2))) =
    (y1 < y2)
    orelse (y1=y2 andalso m1<m2)
    orelse (y1=y2 andalso m1=m2 andalso d1<d2);
    	   
fun number_in_month (dates: (int*int*int) list, month: int) =
    if null dates
    then 0
    else
	let
	    val num = number_in_month (tl dates, month)
	in
	    if #2 (hd dates) = month
	    then 1 + num
	    else 0 + num
	end;		     

fun number_in_months (dates: (int*int*int) list, months: int list) =
    if null months
    then 0
    else number_in_month(dates, hd months) + number_in_months(dates, tl months);

fun exist_int (arr: int list, n: int) =
    if null arr then
	false
    else if hd arr = n then
	true  
    else
	exist_int(tl arr, n);
	
(*
fun number_in_months_challenge (dates: (int*int*int) list, months: int list) =
    let
 
	fun ans_in_the_list (dates, list, in_months: int list) =
	    if (exist_int(in_months, hd months)) then
		1 + number_in_month(dates, hd months) + ans_in_the_list()
	    else
		
    in
	ans_in_the_list([])
    end;
	
   *)


fun dates_in_month (dates: (int*int*int) list, month: int) =
    if null dates
    then []
    else
	let
	    val new_dates = dates_in_month (tl dates, month)
	    val cur_date = hd dates
	in
	    if #2 cur_date = month
	    then cur_date::new_dates
	    else new_dates
	end;	

fun append (xs: (int*int*int) list, ys: (int*int*int) list) =
    if null xs
    then ys
    else (hd xs)::append(tl xs, ys);


fun dates_in_months (dates: (int*int*int) list, months: int list) =
    if null months
    then []
    else append(dates_in_month(dates, hd months), dates_in_months(dates, tl months));

fun get_nth (xs: string list, n: int) =
    if null xs orelse n < 1 then
	""
    else if n = 1 then
	hd xs
    else
	get_nth(tl xs,  n-1);

fun date_to_string (year: int, month: int, day: int): string =
    let
	val months = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"];
    in
	get_nth(months, month) ^ " " ^Int.toString(day) ^ ", " ^ Int.toString(year) 
    end;

fun number_before_reaching_sum (sum: int, xs: int list):int =
    if hd xs >= sum then
	0
    else
        1+number_before_reaching_sum(sum-(hd xs), tl xs);

fun what_month (day: int) =
    let
	val days_in_month = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    in
	 1+number_before_reaching_sum(day, days_in_month)
    end;

fun month_range (day1: int, day2: int): int list =
    if day1 > day2 then
	[]
    else
	what_month(day1) :: month_range(day1+1, day2);
    

fun oldest (dates: (int*int*int) list) =
    if null dates
    then NONE
    else
	let val tl_ans = oldest(tl dates) 
	in
	    if isSome tl_ans andalso is_older(hd dates, valOf tl_ans)
	    then tl_ans
	    else SOME(hd dates)  
	end;
	    
 

	
