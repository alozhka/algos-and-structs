program TestRecordEndError;

type
  TPerson = record
    Name: string;
    Age: integer;
  // Ожидается END для записи
begin
  writeln('This is a record.');
end.
