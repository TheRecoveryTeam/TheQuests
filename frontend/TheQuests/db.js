function func() {
    var aaa="aaaaaaa";
    return aaa;
}
var IDENTIFIER = "Quest_DB";
var VERSION = "";
var DESCRIPTION = "Local DB for Quest data";
var ESTIMATED_SIZE = 1000000;

function dbInit()
{
    var db = LocalStorage.openDatabaseSync(IDENTIFIER, VERSION, DESCRIPTION, ESTIMATED_SIZE);
    try {
        db.transaction(function (tx) {
            tx.executeSql('CREATE TABLE IF NOT EXISTS quest_db (user_id text,' +
                                                                ' nickname text,' +
                                                                ' email text,' +
                                                                ' vk_id text,' +
                                                                ' token text,' +
                                                                ' avatar_path text)');
            });
    } catch (err) {
        console.log("Error creating table in database: " + err);
    };
}

function dbGetHandle()
{
    try {
        var db = LocalStorage.openDatabaseSync(IDENTIFIER, VERSION, DESCRIPTION, ESTIMATED_SIZE);
    } catch (err) {
        console.log("Error opening database: " + err);
    }
    return db;
}

function dbDeleteRows()
{
    var db = dbGetHandle();
    db.transaction(function (tx) {
        tx.executeSql('delete from quest_db');
    });
}

function dbInsert(user_id, nickname, email, vk_id, token, avatar_path)
{
    dbDeleteRows();
    var db = dbGetHandle();
    db.transaction(function (tx) {
        tx.executeSql('INSERT INTO quest_db VALUES(?, ?, ?, ?, ?, ?)',
                      [user_id, nickname, email, vk_id, token, avatar_path]);
    });
}

function dbRead(onSelect)
{
    var db = dbGetHandle();
    var result = {};
    db.transaction(function (tx) {
        var rawResult = tx.executeSql(
                    'SELECT user_id, nickname, email, vk_id, token, avatar_path FROM quest_db');
        if (rawResult.rows.length !== 1) {
            onSelect(null);
        }
        var cur = rawResult.rows[0];
        result.userId = cur.user_id;
        result.nickname = cur.nickname;
        result.email = cur.email;
        result.vkId = cur.vk_id;
        result.token = cur.token;
        result.avatarPath = cur.avatar_path;
        onSelect(result);
    })
}
