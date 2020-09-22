#include "db.h"


string get_date() {
	string y1;
	string temp;
	cout << endl << "year(YYYY):";
	cin >> y1;
	y1 += '-';
	cout << endl << "month(mm):";
	cin >> temp;
	y1 += temp + "-";
	cout << endl << "day(dd):";
	cin >> temp;
	y1 += temp;
	return y1;
}
void db::op1(string y1, string y2) {
	string str = "SELECT count(a_id) FROM album_details_table WHERE s_rec_date>= '" + y1 + "' and e_rec_date <= '" + y2 + "';";

	mysqlx_result_t* res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);

	int64_t x;
	if (NULL != res) {
		char buff[256]; size_t size = 0;

		do {
			mysqlx_row_t* row = mysqlx_row_fetch_one(res);
			while (NULL != row) {
				//size = sizeof(buff);
				mysqlx_get_sint(row, 0, &x);
				cout << "answer: " << x << endl << endl;
				row = mysqlx_row_fetch_one(res);
			}
		} while (RESULT_OK == mysqlx_next_result(res));
	}
	else {
		cerr << mysqlx_error_message(sess) << endl;
		exit(mysqlx_error_num(sess));
	}
}

void db::op2(string y1, string y2, string x) {
	string str = "SELECT count(ms_id) FROM (select id from person_table where name='" + x + "' and job='m') p join musician_in_ms  a on p.id =a.musican_id join music_scene_tedail_table  b on a.m_scene_id=b.ms_id WHERE  b.record_date>= '" + y1 + "' and b.record_date <= '" + y2 + "';";
	mysqlx_result_t* res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	int64_t a;
	if (NULL != res) {
		char buff[256]; size_t size = 0;

		do {
			mysqlx_row_t* row = mysqlx_row_fetch_one(res);
			while (NULL != row) {
				//size = sizeof(buff);
				mysqlx_get_sint(row, 0, &a);
				cout << "answer: " << a << endl << endl;
				row = mysqlx_row_fetch_one(res);
			}
		} while (RESULT_OK == mysqlx_next_result(res));
	}
	else {
		cerr << mysqlx_error_message(sess) << endl;
		exit(mysqlx_error_num(sess));
	}
}


void db::op3(string y1, string y2, string x) {
	string str = "SELECT count(distinct musical_scene_in_album.album_id) FROM (SELECT id FROM person_table WHERE name='" + x + "' AND job='m') P join musician_in_ms on p.id=musician_in_ms.musican_id join music_scene_tedail_table m on m.ms_id=musician_in_ms.m_scene_id join musical_scene_in_album  on musical_scene_in_album.musical_scene_id=musician_in_ms.m_scene_id WHERE m.record_date>='" + y1 + "' AND m.record_date<='" + y2 + "';";
	mysqlx_result_t* res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	int64_t a;
	if (NULL != res) {
		char buff[256]; size_t size = 0;

		do {
			mysqlx_row_t* row = mysqlx_row_fetch_one(res);
			while (NULL != row) {
				//size = sizeof(buff);
				mysqlx_get_sint(row, 0, &a);
				cout << "answer: " << a << endl << endl;
				row = mysqlx_row_fetch_one(res);
			}
		} while (RESULT_OK == mysqlx_next_result(res));
	}
	else {
		cerr << mysqlx_error_message(sess) << endl;
		exit(mysqlx_error_num(sess));
	}
}

void db::op4() {
	string str = "select ins_type from instrument_details_table group by ins_type order by sum(i_amount_in_ms) desc limit 1;";
	mysqlx_result_t* res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	if (NULL != res) {
		char buff[256]; size_t size = 0;

		do {
			mysqlx_row_t* row = mysqlx_row_fetch_one(res);
			while (NULL != row) {
				size = sizeof(buff);
				mysqlx_get_bytes(row, 0, 0, buff, &size);
				cout << "answer: " << buff << endl << endl;
				row = mysqlx_row_fetch_one(res);
			}
		} while (RESULT_OK == mysqlx_next_result(res));
	}
	else {
		cerr << mysqlx_error_message(sess) << endl << endl;
		exit(mysqlx_error_num(sess));
	}
}

void db::op5(string a) {
	string str = "select ins_type, manufacture_name from (select a_id from album_details_table where album_name='" + a + "') as a JOIN musical_scene_in_album on musical_scene_in_album.album_id=a.a_id JOIN musician_in_ms on musical_scene_in_album.musical_scene_id=musician_in_ms.m_scene_id JOIN ins_in_ms on musician_in_ms.participant_id=ins_in_ms.part_id JOIN instrument_details_table on ins_in_ms.instrument_id=instrument_details_table.ins_id;";
	mysqlx_result_t* res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	if (NULL != res) {
		char buff[256]; size_t size = 0;

		do {
			mysqlx_row_t* row = mysqlx_row_fetch_one(res);
			while (NULL != row) {
				size = sizeof(buff);
				mysqlx_get_bytes(row, 0, 0, buff, &size);
				cout << "answer: " << buff << endl << endl;
				row = mysqlx_row_fetch_one(res);
			}
		} while (RESULT_OK == mysqlx_next_result(res));
	}
	else {
		cerr << mysqlx_error_message(sess) << endl << endl;
		exit(mysqlx_error_num(sess));
	}
}

void db::op6(string y1, string y2) {
	string str = "SELECT name from person_table join produce_album on person_table.id=produce_album.p_id join (SELECT a_id from album_details_table WHERE s_rec_date>='" + y1 + "' and e_rec_date<='" + y2 + "') as a on a.a_id=produce_album.a_id GROUP BY produce_album.p_id ORDER BY COUNT(produce_album.a_id) DESC limit 1;";
	mysqlx_result_t* res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	if (NULL != res) {
		char buff[256]; size_t size = 0;

		do {
			mysqlx_row_t* row = mysqlx_row_fetch_one(res);
			while (NULL != row) {
				size = sizeof(buff);
				mysqlx_get_bytes(row, 0, 0, buff, &size);
				cout << "answer: " << buff << endl << endl;
				row = mysqlx_row_fetch_one(res);
			}
		} while (RESULT_OK == mysqlx_next_result(res));
	}
	else {
		cerr << mysqlx_error_message(sess) << endl << endl;
		exit(mysqlx_error_num(sess));
	}
}

void db::op7() {
	string str = "select manufacture_name from instrument_details_table group by manufacture_name order by sum(i_amount_in_ms) desc limit 1;";
	mysqlx_result_t* res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	if (NULL != res) {
		char buff[256]; size_t size = 0;

		do {
			mysqlx_row_t* row = mysqlx_row_fetch_one(res);
			while (NULL != row) {
				size = sizeof(buff);
				mysqlx_get_bytes(row, 0, 0, buff, &size);
				cout << "answer: " << buff << endl << endl;
				row = mysqlx_row_fetch_one(res);
			}
		} while (RESULT_OK == mysqlx_next_result(res));
	}
	else {
		cerr << mysqlx_error_message(sess) << endl << endl;
		exit(mysqlx_error_num(sess));
	}
}

void db::op8() {
	string str = "SELECT count(distinct musican_id) FROM musician_in_ms;";
	mysqlx_result_t* res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	int64_t x;
	if (NULL != res) {
		char buff[256]; size_t size = 0;

		do {
			mysqlx_row_t* row = mysqlx_row_fetch_one(res);
			while (NULL != row) {
				//size = sizeof(buff);
				mysqlx_get_sint(row, 0, &x);
				cout << "the number of between dates:" << x << endl << endl;
				row = mysqlx_row_fetch_one(res);
			}
		} while (RESULT_OK == mysqlx_next_result(res));
	}
	else {
		cerr << mysqlx_error_message(sess) << endl;
		exit(mysqlx_error_num(sess));
	}
}

void db::op9() {
	string str = "select name from musician_in_ms as a CROSS JOIN musician_in_ms as b JOIN person_table as p on a.musican_id=p.id where a.musican_id<>b.musican_id and a.m_scene_id=b.m_scene_id group by a.musican_id order by count(id) desc limit 1;";
	mysqlx_result_t* res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	if (NULL != res) {
		char buff[256]; size_t size = 0;

		do {
			mysqlx_row_t* row = mysqlx_row_fetch_one(res);
			while (NULL != row) {
				size = sizeof(buff);
				mysqlx_get_bytes(row, 0, 0, buff, &size);
				cout << "answer: " << buff << endl << endl;
				row = mysqlx_row_fetch_one(res);
			}
		} while (RESULT_OK == mysqlx_next_result(res));
	}
	else {
		cerr << mysqlx_error_message(sess) << endl << endl;
		exit(mysqlx_error_num(sess));
	}
}

void db::op10() {
	string str = "select ms_genre from instrument_details_table JOIN music_scene_tedail_table group by ms_genre order by sum(i_amount_in_ms) desc limit 1;";
	mysqlx_result_t* res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	if (NULL != res) {
		char buff[256]; size_t size = 0;

		do {
			mysqlx_row_t* row = mysqlx_row_fetch_one(res);
			while (NULL != row) {
				size = sizeof(buff);
				mysqlx_get_bytes(row, 0, 0, buff, &size);
				cout << "answer: " << buff << endl << endl;
				row = mysqlx_row_fetch_one(res);
			}
		} while (RESULT_OK == mysqlx_next_result(res));
	}
	else {
		cerr << mysqlx_error_message(sess) << endl << endl;
		exit(mysqlx_error_num(sess));
	}
}

void db::op11(string y1, string y2) {
	string str = "select name from music_scene_tedail_table as m JOIN person_table as p on m.t_id=p.id where m.record_date between '" + y1 + "' and '" + y2 + "' GROUP BY m.t_id order by count(ms_id) desc limit 1;";
	mysqlx_result_t* res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	if (NULL != res) {
		char buff[256]; size_t size = 0;

		do {
			mysqlx_row_t* row = mysqlx_row_fetch_one(res);
			while (NULL != row) {
				size = sizeof(buff);
				mysqlx_get_bytes(row, 0, 0, buff, &size);
				cout << "answer: " << buff << endl << endl;
				row = mysqlx_row_fetch_one(res);
			}
		} while (RESULT_OK == mysqlx_next_result(res));
	}
	else {
		cerr << mysqlx_error_message(sess) << endl << endl;
		exit(mysqlx_error_num(sess));
	}
}

void db::op12() {
	string str = "select album_name from album_details_table where e_rec_date=(select min(e_rec_date) from album_details_table);";
	mysqlx_result_t* res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	if (NULL != res) {
		char buff[256]; size_t size = 0;

		do {
			mysqlx_row_t* row = mysqlx_row_fetch_one(res);
			while (NULL != row) {
				size = sizeof(buff);
				mysqlx_get_bytes(row, 0, 0, buff, &size);
				cout << "answer: " << buff << endl << endl;
				row = mysqlx_row_fetch_one(res);
			}
		} while (RESULT_OK == mysqlx_next_result(res));
	}
	else {
		cerr << mysqlx_error_message(sess) << endl << endl;
		exit(mysqlx_error_num(sess));
	}
}

void db::op13() {
	string str = "select ms_name from musical_scene_in_album as a JOIN music_scene_tedail_table as b on a.musical_scene_id=b.ms_id where exists(select ms_name from musical_scene_in_album as c JOIN music_scene_tedail_table as d on c.musical_scene_id=d.ms_id where c.musical_scene_id=a.musical_scene_id and c.album_id<>a.album_id) group by ms_name;";
	mysqlx_result_t* res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	if (NULL != res) {
		char buff[256]; size_t size = 0;

		do {
			mysqlx_row_t* row = mysqlx_row_fetch_one(res);
			while (NULL != row) {
				size = sizeof(buff);
				mysqlx_get_bytes(row, 0, 0, buff, &size);
				cout << "answer: " << buff << endl << endl;
				row = mysqlx_row_fetch_one(res);
			}
		} while (RESULT_OK == mysqlx_next_result(res));
	}
	else {
		cerr << mysqlx_error_message(sess) << endl << endl;
		exit(mysqlx_error_num(sess));
	}
}

void db::op14() {
	string str;
	str = "select name from person_table as p JOIN music_scene_tedail_table as a on a.t_id=p.id JOIN musical_scene_in_album as b on a.ms_id=b.musical_scene_id where not exists(select p1.name from person_table as p1 JOIN music_scene_tedail_table as a1 on a1.t_id=p1.id JOIN musical_scene_in_album as b1 on a1.ms_id=b1.musical_scene_id where b1.album_id=b.album_id and a1.t_id<>a.t_id) group by name;";
	mysqlx_result_t* res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	if (NULL != res) {
		char buff[256]; size_t size = 0;

		do {
			mysqlx_row_t* row = mysqlx_row_fetch_one(res);
			while (NULL != row) {
				size = sizeof(buff);
				mysqlx_get_bytes(row, 0, 0, buff, &size);
				cout << "answer: " << buff << endl << endl;
				row = mysqlx_row_fetch_one(res);
			}
		} while (RESULT_OK == mysqlx_next_result(res));
	}
	else {
		cerr << mysqlx_error_message(sess) << endl << endl;
		exit(mysqlx_error_num(sess));
	}
}

void db::op15() {
	string str;
	str = "select p.name from person_table p JOIN musician_in_ms  m on p.id=m.musican_id JOIN music_scene_tedail_table  a on m.m_scene_id=a.ms_id group by m.musican_id order by count(distinct a.ms_genre) desc limit 1;";
	mysqlx_result_t* res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	if (NULL != res) {
		char buff[256]; size_t size = 0;

		do {
			mysqlx_row_t* row = mysqlx_row_fetch_one(res);
			while (NULL != row) {
				size = sizeof(buff);
				mysqlx_get_bytes(row, 0, 0, buff, &size);
				cout << "answer: " << buff << endl << endl;
				row = mysqlx_row_fetch_one(res);
			}
		} while (RESULT_OK == mysqlx_next_result(res));
	}
	else {
		cerr << mysqlx_error_message(sess) << endl << endl;
		exit(mysqlx_error_num(sess));
	}
}
db::db()
{
	char err_msg[256] = {};
	int err_code = 0;

	//creration of an sql connection aka session to the mysql server
	sess = mysqlx_get_session("localhost", DEFAULT_MYSQLX_PORT, "root", "root", "", err_msg, &err_code);
	if (NULL == sess) {
		cerr << err_msg << endl;
		exit(err_code);
	}
	string str = "DROP SCHEMA IF  EXISTS `lol`;";
	mysqlx_result_t* res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = "CREATE SCHEMA IF NOT EXISTS `lol`;";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	sess = mysqlx_get_session("localhost", DEFAULT_MYSQLX_PORT, "root", "root", "lol", err_msg, &err_code);
	create_tables();
	init();
}

void db::create_tables() {
	char err_msg[256] = {};
	int err_code = 0;
	string str;
	mysqlx_result_t* res;
	str = "CREATE TABLE `lol`.`person_table` (`id` INT NOT NULL AUTO_INCREMENT,`name` VARCHAR(45) NULL,`job` VARCHAR(45) NULL,PRIMARY KEY(`id`));";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = "CREATE TABLE `lol`.`musician_details_table` (`m_id` INT NOT NULL AUTO_INCREMENT,`m_address` VARCHAR(45) NOT NULL,`m_type` INT NOT NULL,`phone_number` VARCHAR(10) NOT NULL,`song_amount` INT NOT NULL DEFAULT 0,PRIMARY KEY(`m_id`),	CONSTRAINT `m_id` FOREIGN KEY(`m_id`) REFERENCES `lol`.`person_table` (`id`) ON DELETE CASCADE ON UPDATE CASCADE); ";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = "CREATE TABLE `lol`.`instrument_details_table` (`ins_id` INT NOT NULL AUTO_INCREMENT,`ins_type` VARCHAR(45) NOT NULL,`manufacture_name` VARCHAR(45) NOT NULL,`i_amount_in_ms` INT NULL DEFAULT 0,PRIMARY KEY(`ins_id`)); ";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " CREATE TABLE `lol`.`album_details_table` (`a_id` INT NOT NULL AUTO_INCREMENT,`album_name` VARCHAR(45) NOT NULL,`num_of_songs` INT NOT NULL DEFAULT 0,`s_rec_date` DATE NOT NULL,`e_rec_date` DATE NOT NULL,PRIMARY KEY(`a_id`)); ";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = "CREATE TABLE `lol`.`music_scene_tedail_table` (`ms_id` INT NOT NULL AUTO_INCREMENT,`ms_name` VARCHAR(45) NOT NULL,`record_date` DATE NOT NULL,`length` INT NOT NULL,`ms_genre` VARCHAR(45) NOT NULL,`t_id` INT NOT NULL,`autor_id` INT NOT NULL,`composer_id` INT NOT NULL,PRIMARY KEY(`ms_id`),INDEX `t_id_idx` (`t_id` ASC) VISIBLE,INDEX `autor_id_idx` (`autor_id` ASC) VISIBLE,INDEX `composer_id_idx` (`composer_id` ASC) VISIBLE,CONSTRAINT `t_id` FOREIGN KEY(`t_id`) REFERENCES `lol`.`person_table` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION,CONSTRAINT `autor_id` FOREIGN KEY(`autor_id`) REFERENCES `lol`.`person_table` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION,CONSTRAINT `composer_id` FOREIGN KEY(`composer_id`) REFERENCES `lol`.`person_table` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION);";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = "CREATE TABLE `lol`.`produce_album` (`p_id` INT NOT NULL,`a_id` INT NOT NULL,PRIMARY KEY(`p_id`, `a_id`),INDEX `a_id_idx` (`a_id` ASC) VISIBLE,CONSTRAINT `p_id` FOREIGN KEY(`p_id`) REFERENCES `lol`.`person_table` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION, CONSTRAINT `a_id` FOREIGN KEY(`a_id`) REFERENCES `lol`.`album_details_table` (`a_id`) ON DELETE NO ACTION ON UPDATE NO ACTION);";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = "CREATE TABLE `lol`.`musician_play_ins` (`musican_id` INT NOT NULL,`ins_type` VARCHAR(45) NOT NULL,PRIMARY KEY(`musican_id`,`ins_type`),CONSTRAINT `musician_id` FOREIGN KEY(`musican_id`) REFERENCES `lol`.`musician_details_table` (`m_id`) ON DELETE NO ACTION ON UPDATE NO ACTION); ";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = "CREATE TABLE `lol`.`musical_scene_in_album` (`album_id` INT NOT NULL,`musical_scene_id` INT NOT NULL,PRIMARY KEY(`album_id`, `musical_scene_id`),INDEX `musical_scene_id_idx` (`musical_scene_id` ASC) VISIBLE,CONSTRAINT `album_id` FOREIGN KEY(`album_id`) REFERENCES `lol`.`album_details_table` (`a_id`)	ON DELETE NO ACTION	ON UPDATE NO ACTION,CONSTRAINT `musical_scene_id` FOREIGN KEY(`musical_scene_id`) REFERENCES `lol`.`music_scene_tedail_table` (`ms_id`) ON DELETE NO ACTION	ON UPDATE NO ACTION); ";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = "	CREATE TABLE `lol`.`musician_in_ms` (`musican_id` INT NOT NULL,`m_scene_id` INT NOT NULL,`participant_id` INT NOT NULL AUTO_INCREMENT,PRIMARY KEY(`participant_id`),INDEX `musican_id_idx` (`musican_id` ASC) VISIBLE,INDEX `m_scene_id_idx` (`m_scene_id` ASC) VISIBLE,CONSTRAINT `musican_id`	FOREIGN KEY(`musican_id`) REFERENCES `lol`.`musician_details_table` (`m_id`) ON DELETE NO ACTION ON UPDATE NO ACTION,CONSTRAINT `m_scene_id`FOREIGN KEY(`m_scene_id`) REFERENCES `lol`.`music_scene_tedail_table` (`ms_id`) ON DELETE NO ACTION	ON UPDATE NO ACTION); ";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = "	CREATE TABLE `lol`.`ins_in_ms` (`part_id` INT NOT NULL,`instrument_id` INT NOT NULL,PRIMARY KEY(`part_id`),INDEX `instrument_id_idx` (`instrument_id` ASC) VISIBLE,CONSTRAINT `part_id` FOREIGN KEY(`part_id`) REFERENCES `lol`.`musician_in_ms` (`participant_id`)	ON DELETE NO ACTION	ON UPDATE NO ACTION, CONSTRAINT `instrument_id` FOREIGN KEY(`instrument_id`) REFERENCES `lol`.`instrument_details_table` (`ins_id`) ON DELETE NO ACTION	ON UPDATE NO ACTION); ";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	/*סוף יצירת הטבלאות בDB*/

	/*משנים את sess ומוסיפים את שהם של הסכמה שיצרנו כדי שנדע לאיזה מאגר לפנות*/
	//sess = mysqlx_get_session("localhost", DEFAULT_MYSQLX_PORT, "root", "root", "lol", err_msg, &err_code);
	/*char query1[] = { "show tables" };
	res = mysqlx_sql(sess, query1, MYSQLX_NULL_TERMINATED);

	if (NULL != res) {
		char buff[1000000]; size_t size = 0;

		do {
			mysqlx_row_t* row = mysqlx_row_fetch_one(res);
			while (NULL != row) {
				size = sizeof(buff);
				mysqlx_get_bytes(row, 0, 0, buff, &size);
				cout << buff << endl;
				row = mysqlx_row_fetch_one(res);
			}
		} while (RESULT_OK == mysqlx_next_result(res));
	}
	else {
		cerr << mysqlx_error_message(sess) << endl;
		exit(mysqlx_error_num(sess));
	}

	cout << "------------------------" << endl; }*/
}
void db::init()
{
	char err_msg[256] = {};
	int err_code = 0;
	string str;
	mysqlx_result_t* res;

	/**********************album_details_table************************/
	str = "INSERT INTO `lol`.`album_details_table` ( `album_name`, `num_of_songs`, `s_rec_date`, `e_rec_date`) VALUES ( 'a', '2', '2018-02-01', '2018-04-05');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`album_details_table` ( `album_name`, `num_of_songs`, `s_rec_date`, `e_rec_date`) VALUES ( 'trees', '1', '2018-04-01', '2018-05-10');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`album_details_table` (`album_name`, `num_of_songs`, `s_rec_date`, `e_rec_date`) VALUES('love', '2', '2018-01-01', '2018-02-20');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`album_details_table` (`album_name`, `num_of_songs`, `s_rec_date`, `e_rec_date`) VALUES('banana', '2', '2018-02-01', '2018-06-20');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`album_details_table` (`album_name`, `num_of_songs`, `s_rec_date`, `e_rec_date`) VALUES('dog', '1', '2018-06-23', '2018-07-29');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`album_details_table` (`album_name`, `num_of_songs`, `s_rec_date`, `e_rec_date`) VALUES('cpp', '1', '2018-07-13', '2018-08-24');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`album_details_table` (`album_name`, `num_of_songs`, `s_rec_date`, `e_rec_date`) VALUES('master', '1', '2018-08-01', '2018-10-01');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`album_details_table` (`album_name`, `num_of_songs`, `s_rec_date`, `e_rec_date`) VALUES('new', '1', '2018-09-20', '2018-10-02');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`album_details_table` (`album_name`, `num_of_songs`, `s_rec_date`, `e_rec_date`) VALUES('phonix', '1', '2018-01-01', '2018-01-15');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`album_details_table` (`album_name`, `num_of_songs`, `s_rec_date`, `e_rec_date`) VALUES('lion', '1', '2018-01-30', '2018-02-25'); ";
	//cout << str.c_str();
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	/***********************instrument_details_table***************************/

	str = " INSERT INTO `lol`.`instrument_details_table` (`ins_type`, `manufacture_name`, `i_amount_in_ms`) VALUES('guitar', 'gibson', '1'); ";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = "INSERT INTO `lol`.`instrument_details_table` ( `ins_type`, `manufacture_name`, `i_amount_in_ms`) VALUES ( 'guitar', 'fender', '1');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = "INSERT INTO `lol`.`instrument_details_table` ( `ins_type`, `manufacture_name`, `i_amount_in_ms`) VALUES ( 'piano', 'wind', '1');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`instrument_details_table` ( `ins_type`, `manufacture_name`, `i_amount_in_ms`) VALUES ( 'piano', 'musicx', '1');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`instrument_details_table` ( `ins_type`, `manufacture_name`, `i_amount_in_ms`) VALUES ( 'drums', 'musicx', '0');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`instrument_details_table` ( `ins_type`, `manufacture_name`, `i_amount_in_ms`) VALUES ( 'drums', 'gibson', '1');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`instrument_details_table` ( `ins_type`, `manufacture_name`, `i_amount_in_ms`) VALUES ('flute', 'fender', '1');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`instrument_details_table` ( `ins_type`, `manufacture_name`, `i_amount_in_ms`) VALUES ( 'flute', 'wind', '1');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = "INSERT INTO `lol`.`instrument_details_table` ( `ins_type`, `manufacture_name`, `i_amount_in_ms`) VALUES ( 'trumpet', 'wind', '2'); ";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = "INSERT INTO `lol`.`instrument_details_table` ( `ins_type`, `manufacture_name`, `i_amount_in_ms`) VALUES ( 'trumpet', 'music inc', '1');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	/****************person_table******************/

	str = " INSERT INTO `lol`.`person_table` ( `name`, `job`) VALUES ( 'omer', 'm');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`person_table` ( `name`, `job`) VALUES ( 'eden', 'm');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`person_table` ( `name`, `job`) VALUES ( 'ivri', 'm');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`person_table` ( `name`, `job`) VALUES ( 'aviv', 'm');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`person_table` ( `name`, `job`) VALUES ( 'itzik', 'm');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`person_table` ( `name`, `job`) VALUES ( 'zohar', 'm');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`person_table` ( `name`, `job`) VALUES ( 'sarit', 'm');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`person_table` ( `name`, `job`) VALUES ( 'eli', 'm');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`person_table` ( `name`, `job`) VALUES ( 'rotem', 'm');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`person_table` ( `name`, `job`) VALUES ( 'ofra', 'm');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`person_table` ( `name`, `job`) VALUES ( 'dana', 'p');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`person_table` ( `name`, `job`) VALUES ( 'udi', 'p');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`person_table` ( `name`, `job`) VALUES ( 'dany', 't');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`person_table` ( `name`, `job`) VALUES ( 'noa', 't');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`person_table` ( `name`, `job`) VALUES ('michael', 'a');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`person_table` ( `name`, `job`) VALUES ( 'nirit', 'a');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`person_table` ( `name`, `job`) VALUES ( 'adi', 'c');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`person_table` ( `name`, `job`) VALUES ( 'amos', 'c');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	/***********************music_scene_tedail_table***********************/

	str = " INSERT INTO `lol`.`music_scene_tedail_table` ( `ms_name`, `record_date`, `length`, `ms_genre`, `t_id`, `autor_id`, `composer_id`) VALUES ( 'wind', '2018-01-01', '180', 'rock', '13', '15', '18');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`music_scene_tedail_table` ( `ms_name`, `record_date`, `length`, `ms_genre`, `t_id`, `autor_id`, `composer_id`) VALUES ( 'roots', '2018-02-01', '240', 'classic', '13', '16', '17');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`music_scene_tedail_table` ( `ms_name`, `record_date`, `length`, `ms_genre`, `t_id`, `autor_id`, `composer_id`) VALUES ( 'late', '2018-03-01', '187', 'classic', '14', '15', '18');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`music_scene_tedail_table` ( `ms_name`, `record_date`, `length`, `ms_genre`, `t_id`, `autor_id`, `composer_id`) VALUES ( 'all about', '2018-04-01', '200', 'hip hop', '13', '15', '18');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`music_scene_tedail_table` ( `ms_name`, `record_date`, `length`, `ms_genre`, `t_id`, `autor_id`, `composer_id`) VALUES ( 'river', '2018-05-01', '202', 'rock', '13', '16', '17');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`music_scene_tedail_table` ( `ms_name`, `record_date`, `length`, `ms_genre`, `t_id`, `autor_id`, `composer_id`) VALUES ( 'song2', '2018-06-01', '300', 'rock', '14', '16', '18');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`music_scene_tedail_table` ( `ms_name`, `record_date`, `length`, `ms_genre`, `t_id`, `autor_id`, `composer_id`) VALUES ( 'help', '2018-07-01', '304', 'hip hop', '14', '15', '17');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`music_scene_tedail_table` ( `ms_name`, `record_date`, `length`, `ms_genre`, `t_id`, `autor_id`, `composer_id`) VALUES ('goodbye', '2018-08-01', '189', 'rock', '13', '16', '18');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`music_scene_tedail_table` ( `ms_name`, `record_date`, `length`, `ms_genre`, `t_id`, `autor_id`, `composer_id`) VALUES ( 'hello', '2018-09-01', '193', 'hip hop', '14', '15', '17');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`music_scene_tedail_table` ( `ms_name`, `record_date`, `length`, `ms_genre`, `t_id`, `autor_id`, `composer_id`) VALUES ( 'osher', '2018-10-01', '215', 'rock', '14', '16', '17');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	/********************musical_scene_in_album*********************/
	str = " INSERT INTO `lol`.`musical_scene_in_album` (`album_id`, `musical_scene_id`) VALUES ('1', '4');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`musical_scene_in_album` (`album_id`, `musical_scene_id`) VALUES ('1', '3');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`musical_scene_in_album` (`album_id`, `musical_scene_id`) VALUES ('3', '1');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`musical_scene_in_album` (`album_id`, `musical_scene_id`) VALUES ('3', '2');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`musical_scene_in_album` (`album_id`, `musical_scene_id`) VALUES ('2', '5');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`musical_scene_in_album` (`album_id`, `musical_scene_id`) VALUES ('4', '6');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`musical_scene_in_album` (`album_id`, `musical_scene_id`) VALUES ('4', '2');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`musical_scene_in_album` (`album_id`, `musical_scene_id`) VALUES ('5', '7');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`musical_scene_in_album` (`album_id`, `musical_scene_id`) VALUES ('6', '8');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`musical_scene_in_album` (`album_id`, `musical_scene_id`) VALUES ('7', '9');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`musical_scene_in_album` (`album_id`, `musical_scene_id`) VALUES ('10', '2');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`musical_scene_in_album` (`album_id`, `musical_scene_id`) VALUES ('8', '10');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`musical_scene_in_album` (`album_id`, `musical_scene_id`) VALUES ('9', '1');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	/******************musician_details_table*************/
	str = " INSERT INTO `lol`.`musician_details_table` (`m_id`, `m_address`, `m_type`, `phone_number`, `song_amount`) VALUES ('1', 'holon', '2', '0501234567', '1');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`musician_details_table` (`m_id`, `m_address`, `m_type`, `phone_number`, `song_amount`) VALUES ('2', 'tel aviv', '2', '0511234567', '2');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`musician_details_table` (`m_id`, `m_address`, `m_type`, `phone_number`, `song_amount`) VALUES ('3', 'ramla', '2', '0521234567', '1');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`musician_details_table` (`m_id`, `m_address`, `m_type`, `phone_number`, `song_amount`) VALUES ('4', 'tel aviv', '2', '0531234567', '1');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`musician_details_table` (`m_id`, `m_address`, `m_type`, `phone_number`, `song_amount`) VALUES ('5', 'natanya', '2', '0541234567', '1');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`musician_details_table` (`m_id`, `m_address`, `m_type`, `phone_number`, `song_amount`) VALUES ('6', 'eilat', '0', '0551234567', '3');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`musician_details_table` (`m_id`, `m_address`, `m_type`, `phone_number`, `song_amount`) VALUES ('7', 'haifa', '2', '0561234567', '2');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`musician_details_table` (`m_id`, `m_address`, `m_type`, `phone_number`, `song_amount`) VALUES ('8', 'kiryat shmona', '2', '0571234567', '1');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`musician_details_table` (`m_id`, `m_address`, `m_type`, `phone_number`, `song_amount`) VALUES ('9', 'haifa', '1', '0581234567', '1');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`musician_details_table` (`m_id`, `m_address`, `m_type`, `phone_number`, `song_amount`) VALUES ('10', 'holon', '2', '0591234567', '2');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	/*****************musician_in_ms**************/



	str = "INSERT INTO `lol`.`musician_in_ms` (`musican_id`, `m_scene_id`) VALUES ('2', '1'); ";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " INSERT INTO `lol`.`musician_in_ms` (`musican_id`, `m_scene_id`) VALUES ('4', '1' );";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " INSERT INTO `lol`.`musician_in_ms` (`musican_id`, `m_scene_id`) VALUES ('6', '2');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " INSERT INTO `lol`.`musician_in_ms` (`musican_id`, `m_scene_id`) VALUES ('5', '3');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " INSERT INTO `lol`.`musician_in_ms` (`musican_id`, `m_scene_id`) VALUES ('8', '3');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " INSERT INTO `lol`.`musician_in_ms` (`musican_id`, `m_scene_id`) VALUES ('6', '4');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " INSERT INTO `lol`.`musician_in_ms` (`musican_id`, `m_scene_id`) VALUES ('7', '5');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " INSERT INTO `lol`.`musician_in_ms` (`musican_id`, `m_scene_id`) VALUES ('7', '6');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " INSERT INTO `lol`.`musician_in_ms` (`musican_id`, `m_scene_id`) VALUES ('9', '7');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " INSERT INTO `lol`.`musician_in_ms` (`musican_id`, `m_scene_id`) VALUES ('3', '7');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " INSERT INTO `lol`.`musician_in_ms` (`musican_id`, `m_scene_id`) VALUES ('10', '8');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " INSERT INTO `lol`.`musician_in_ms` (`musican_id`, `m_scene_id`) VALUES ('1', '8');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();


	str = "INSERT INTO `lol`.`musician_in_ms` (`musican_id`, `m_scene_id`) VALUES ('10', '9'); ";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " INSERT INTO `lol`.`musician_in_ms` (`musican_id`, `m_scene_id`) VALUES ('2', '10');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();


	str = "INSERT INTO `lol`.`musician_in_ms` (`musican_id`, `m_scene_id`) VALUES ('6', '10'); ";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();


	/****************ins_in_ms***************/



	str = " INSERT INTO `lol`.`ins_in_ms` (`part_id`, `instrument_id`) VALUES ('1', '9');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " INSERT INTO `lol`.`ins_in_ms` (`part_id`, `instrument_id`) VALUES ('2', '8');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " INSERT INTO `lol`.`ins_in_ms` (`part_id`, `instrument_id`) VALUES ('4', '6');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " INSERT INTO `lol`.`ins_in_ms` (`part_id`, `instrument_id`) VALUES ('5', '4');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " INSERT INTO `lol`.`ins_in_ms` (`part_id`, `instrument_id`) VALUES ('8', '3');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " INSERT INTO `lol`.`ins_in_ms` (`part_id`, `instrument_id`) VALUES ('9', '7');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " INSERT INTO `lol`.`ins_in_ms` (`part_id`, `instrument_id`) VALUES ('10', '9');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " INSERT INTO `lol`.`ins_in_ms` (`part_id`, `instrument_id`) VALUES ('11', '1');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " INSERT INTO `lol`.`ins_in_ms` (`part_id`, `instrument_id`) VALUES ('13', '2');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = "INSERT INTO `lol`.`ins_in_ms` (`part_id`, `instrument_id`) VALUES ('14', '10'); ";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	/****************musician_play_ins***************/


	str = " INSERT INTO `lol`.`musician_play_ins` (`musican_id`, `ins_type`) VALUES ('1', 'guitar');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = "INSERT INTO `lol`.`musician_play_ins` (`musican_id`, `ins_type`) VALUES ('1', 'drums'); ";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = "INSERT INTO `lol`.`musician_play_ins` (`musican_id`, `ins_type`) VALUES ('2', 'trumpet'); ";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " INSERT INTO `lol`.`musician_play_ins` (`musican_id`, `ins_type`) VALUES ('3', 'flute');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " INSERT INTO `lol`.`musician_play_ins` (`musican_id`, `ins_type`) VALUES ('3', 'trumpet');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = "INSERT INTO `lol`.`musician_play_ins` (`musican_id`, `ins_type`) VALUES ('4', 'flute'); ";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " INSERT INTO `lol`.`musician_play_ins` (`musican_id`, `ins_type`) VALUES ('5', 'drums');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " INSERT INTO `lol`.`musician_play_ins` (`musican_id`, `ins_type`) VALUES ('5', 'guitar');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " INSERT INTO `lol`.`musician_play_ins` (`musican_id`, `ins_type`) VALUES ('7', 'piano');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " INSERT INTO `lol`.`musician_play_ins` (`musican_id`, `ins_type`) VALUES ('8', 'piano');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " INSERT INTO `lol`.`musician_play_ins` (`musican_id`, `ins_type`) VALUES ('9', 'guitar');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " INSERT INTO `lol`.`musician_play_ins` (`musican_id`, `ins_type`) VALUES ('9', 'piano');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = "INSERT INTO `lol`.`musician_play_ins` (`musican_id`, `ins_type`) VALUES ('9', 'drums'); ";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = "INSERT INTO `lol`.`musician_play_ins` (`musican_id`, `ins_type`) VALUES ('9', 'flute'); ";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " INSERT INTO `lol`.`musician_play_ins` (`musican_id`, `ins_type`) VALUES ('9', 'trumpet');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();


	str = " INSERT INTO `lol`.`musician_play_ins` (`musican_id`, `ins_type`) VALUES ('10', 'guitar');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = "INSERT INTO `lol`.`musician_play_ins` (`musican_id`, `ins_type`) VALUES ('10', 'piano'); ";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " INSERT INTO `lol`.`musician_play_ins` (`musican_id`, `ins_type`) VALUES ('10', 'drums');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " INSERT INTO `lol`.`musician_play_ins` (`musican_id`, `ins_type`) VALUES ('10', 'flute');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	str = " INSERT INTO `lol`.`musician_play_ins` (`musican_id`, `ins_type`) VALUES ('10', 'trumpet');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();

	/*****************produce_album**************/

	str = " INSERT INTO `lol`.`produce_album` (`p_id`, `a_id`) VALUES ('11', '1');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`produce_album` (`p_id`, `a_id`) VALUES ('12', '1');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`produce_album` (`p_id`, `a_id`) VALUES ('11', '2');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`produce_album` (`p_id`, `a_id`) VALUES ('12', '3');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`produce_album` (`p_id`, `a_id`) VALUES ('11', '3');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = "INSERT INTO `lol`.`produce_album` (`p_id`, `a_id`) VALUES ('11', '4'); ";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`produce_album` (`p_id`, `a_id`) VALUES ('12', '4');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`produce_album` (`p_id`, `a_id`) VALUES ('12', '5');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`produce_album` (`p_id`, `a_id`) VALUES ('12', '6');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`produce_album` (`p_id`, `a_id`) VALUES ('11', '6');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`produce_album` (`p_id`, `a_id`) VALUES ('11', '7');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`produce_album` (`p_id`, `a_id`) VALUES ('12', '8');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = "INSERT INTO `lol`.`produce_album` (`p_id`, `a_id`) VALUES ('11', '8'); ";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = "INSERT INTO `lol`.`produce_album` (`p_id`, `a_id`) VALUES ('11', '9'); ";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`produce_album` (`p_id`, `a_id`) VALUES ('12', '9');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`produce_album` (`p_id`, `a_id`) VALUES ('11', '10');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();
	str = " INSERT INTO `lol`.`produce_album` (`p_id`, `a_id`) VALUES ('12', '10');";
	res = mysqlx_sql(sess, str.c_str(), MYSQLX_NULL_TERMINATED);
	str.clear();



	/*******************************/
}

db::~db()
{
	mysqlx_session_close(sess);
}
