-- Создаём расширение (если ещё не создано)
CREATE EXTENSION IF NOT EXISTS odbc_fdw;

-- Удалим сервер, если уже есть (на всякий случай)
DROP SERVER IF EXISTS mssql_server_test CASCADE;

-- Создаём сервер ODBC
CREATE SERVER mssql_server_test
FOREIGN DATA WRAPPER odbc_fdw
OPTIONS (dsn 'MSSQL_CSC');

-- Создаём отображение пользователя
CREATE USER MAPPING FOR CURRENT_USER
SERVER mssql_server_test
OPTIONS (odbc_UID 'evg_reader', odbc_PWD 'evg_$ecur!ty');

-- Создаём внешний foreign table
CREATE FOREIGN TABLE mssql_table 
(
  sales_date Timestamp,
  sales_units Float,
  sales_rub Float,
  nomenkl_code Varchar,
  nomenkl_name Varchar,
  nomenkl_full_name Varchar,
  seriya_num Varchar,
  seriya_expiry_date Timestamp,
  partner_name_unif Varchar,
  kontragent_name_unif Varchar,
  kontragent_INN Varchar,
  srok_godn Float
)

SERVER mssql_server_test

OPTIONS (
  sql_query '
    SELECT 
      DATEADD(YEAR, -2000,t_fact._period) AS sales_date,
      t_fact._fld40831 AS sales_units,
      t_fact._fld40833 AS sales_rub,
      CAST(t_nomenkl._Code AS VARCHAR) AS nomenkl_code,
      CAST(t_nomenkl._description AS VARCHAR) AS nomenkl_name,
      CAST(t_nomenkl._fld51090 AS VARCHAR) AS nomenkl_full_name,
      CAST(t_seriya._fld56296 AS VARCHAR) AS seriya_num,
      DATEADD(YEAR, -2000,t_seriya._fld56294) AS seriya_expiry_date,
      CAST(t_partner._fld52657 AS VARCHAR) AS partner_name_unif,
      CAST(t_kontragent._fld50306 AS VARCHAR) AS kontragent_name_unif,
      CAST(t_kontragent._fld50300 AS VARCHAR) AS kontragent_INN,
      t_sroki_godn.srok_godn
    FROM 
      _AccumRg40811 t_fact
    LEFT JOIN _reference242 t_map ON t_fact._fld40812rref = t_map._idrref
    LEFT JOIN _reference290x1 t_nomenkl ON t_map._fld50041rref = t_nomenkl._idrref
    LEFT JOIN _reference498x1 t_seriya ON t_map._fld50043rref = t_seriya._idrref
    LEFT JOIN _reference244 t_partner_mapping ON t_fact._fld40814rref = t_partner_mapping._idrref
    LEFT JOIN _reference255 t_kontragent ON t_partner_mapping._fld50058_rrref = t_kontragent._idrref
    LEFT JOIN _reference357x1 t_partner ON t_partner_mapping._fld50056rref = t_partner._idrref
    LEFT JOIN (
      SELECT _reference290_idrref AS id, _fld51155_n AS srok_godn
      FROM _reference290_vt51152x1
      WHERE _Fld51154RREF = CAST(0xadb9101f743b037d11e4b386f9b5e4a7 AS VARBINARY)
    ) t_sroki_godn ON t_map._fld50041rref = t_sroki_godn.id
  ',
  row_estimate_method 'showplan_all'
);

-- Проверим данные
SELECT * FROM mssql_table LIMIT 10;