describe 'database' do
  before do
    `rm -rf *.db sqlite.db`
  end

  def run_script(commands)
    raw_output = nil
    IO.popen("./sqlite test.db", "r+") do |pipe|
      commands.each do |command|
        pipe.puts command
      end
      pipe.close_write
      raw_output = pipe.read
    end
    raw_output.split("\n")
  end

  it 'inserts and retrieves a row' do
    result = run_script([
      "insert 1 user1 person1@example.com",
      "select",
      ".exit",
    ])
    expect(result).to match_array([
      "db > Executed.",
      "db > (1, user1, person1@example.com)",
      "Executed.",
      "db > ",
    ])
  end

  it 'keeps data after closing connection' do
    res = run_script([
      "insert 1 user1 person1@example.com",
      ".exit"
    ])
    expect(res).to match_array([
      "db > Executed.",
      "db > ",
    ])

    res2 = run_script([
      "select",
      ".exit",
    ])
    expect(res2).to match_array([
      "db > (1, user1, person1@example.com)",
      "Executed.",
      "db > ",
    ])
  end

  it 'prints error message when table is full' do
    script = (1..1401).map do |i|
      "insert #{i} user#{i} person#{i}@example.com"
    end
    script << ".exit"
    result = run_script(script)
    expect(result[-2]).to eq("db > Error: Table full.")
  end

  it 'allows inserting strings that are the maximum length' do
    long_username = "a" * 32
    long_email = "a" * 255
    script = [
      "insert 1 #{long_username} #{long_email}",
      "select",
      ".exit",
    ]
    result = run_script(script)
    expect(result).to match_array([
      "db > Executed.",
      "db > (1, #{long_username}, #{long_email})",
      "Executed.",
      "db > ",
    ])
  end

  it 'prints error message if strings are too long' do
    long_username = "a" * 33
    long_email = "a" * 256
    script = [
      "insert 1 #{long_username} #{long_email}",
      "select",
      ".exit",
    ]
    result = run_script(script)
    expect(result).to match_array([
      "db > String is too long.",
      "db > Executed.",
      "db > ",
    ])
  end
end
