-- RedefineTables
PRAGMA defer_foreign_keys=ON;
PRAGMA foreign_keys=OFF;
CREATE TABLE "new_sensor_information" (
    "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    "soil_sensor" INTEGER,
    "noise_sensor" INTEGER,
    "createdAt" DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP
);
INSERT INTO "new_sensor_information" ("createdAt", "id", "noise_sensor", "soil_sensor") SELECT "createdAt", "id", "noise_sensor", "soil_sensor" FROM "sensor_information";
DROP TABLE "sensor_information";
ALTER TABLE "new_sensor_information" RENAME TO "sensor_information";
PRAGMA foreign_keys=ON;
PRAGMA defer_foreign_keys=OFF;
