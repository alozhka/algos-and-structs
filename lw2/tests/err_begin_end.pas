program TestBeginEndError;

begin
  writeln('This is a begin block.');
  if true then
  begin
    writeln('Nested begin block.');
  // Ожидается END для вложенного блока
end.
