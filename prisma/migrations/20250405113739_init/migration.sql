-- CreateTable
CREATE TABLE "User" (
    "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    "name" TEXT NOT NULL,
    "email" TEXT NOT NULL,
    "password" TEXT NOT NULL,
    "role" TEXT NOT NULL,
    "isDeleted" BOOLEAN NOT NULL DEFAULT false,
    "rememberMe" BOOLEAN NOT NULL DEFAULT false,
    "refreshToken" TEXT,
    "createdAt" DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "updatedAt" DATETIME NOT NULL
);

-- CreateTable
CREATE TABLE "user_helath_details" (
    "emp_id" TEXT NOT NULL PRIMARY KEY,
    "name" TEXT,
    "spo2" INTEGER DEFAULT 0,
    "bpm" INTEGER DEFAULT 0,
    "weight" INTEGER DEFAULT 0,
    "height" INTEGER DEFAULT 0,
    "bmi" REAL DEFAULT 0.00,
    "chest" INTEGER DEFAULT 0,
    "waist" INTEGER DEFAULT 0,
    "isDeleted" BOOLEAN NOT NULL DEFAULT false,
    "body_details" TEXT,
    "createdAt" DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "updatedAt" DATETIME NOT NULL
);

-- CreateTable
CREATE TABLE "sensor_information" (
    "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    "soil_sensor" INTEGER NOT NULL,
    "noise_sensor" INTEGER NOT NULL,
    "createdAt" DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP
);

-- CreateIndex
CREATE UNIQUE INDEX "User_email_key" ON "User"("email");
