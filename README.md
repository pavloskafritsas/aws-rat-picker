# AWS Remote Access Tool (Picker)

This application is a lightweight wrapper around the shell script [AWS RAT](https://github.com/gadamo/aws_rat). It simplifies the process of interacting with multiple AWS profiles stored in `~/.aws/credentials` by providing an easy-to-use menu for selecting and configuring your environment for remote access.

## Features

- Automatically reads all profiles from your `~/.aws/credentials` file.
- Displays a menu for you to easily select the desired AWS profile.
- Sets all the required environment variables for the selected profile.
- Executes the [AWS RAT](https://github.com/gadamo/aws_rat) script with the configured environment.

## Installation

### Prerequisites

- **AWS RAT Script**: Clone [AWS RAT](https://github.com/gadamo/aws_rat) into `~/Projects/Prosperty` directory.
- **AWS CLI**: Ensure that the AWS Command Line Interface is installed and configured with profiles in `~/.aws/credentials`.
- **iniparser**: This application depends on the `iniparser` library for reading and parsing INI files.
- **Shell Environment**: This tool is designed to work in Linux environments.

### Steps

1. Clone this repository:

   ```bash
   git clone https://github.com/pavloskafritsas/aws-rat-picker.git
   cd aws-rat-picker
   ```

2. Build the application using Makefile:

   ```bash
   make
   ```

3. Install (optional)

   ```bash
   sudo make install
   ```

## Usage

1. Run the Application:

   ```bash
   ./aws-rat-picker
   ```

2. Profile Selection:

   The tool will automatically load all profiles from your `~/.aws/credentials` file.

   You will see a menu with all the profiles listed.

   Select the profile by entering the corresponding number (e.g., 1 for the first profile, 2 for the second, etc.), and then press Enter.

3. AWS RAT Execution:

   Once you've selected a profile, the tool will set the necessary environment variables and execute the [AWS RAT](https://github.com/gadamo/aws_rat) script with the selected profile.

4. Stay Running:

   After the [AWS RAT](https://github.com/gadamo/aws_rat) script has been executed, the application will stay running, allowing you to select and execute additional profiles without restarting the application. Simply select another profile by entering its corresponding number.

## Configuration

The AWS profiles are automatically loaded from the `~/.aws/credentials` file.

Each profile should be configured properly in that file.

Example of `~/.aws/credentials` file:

```ini
[profile-1]
aws_access_key_id = YOUR_ACCESS_KEY
aws_secret_access_key = YOUR_SECRET_KEY
region = us-west-2

[profile-2]
aws_access_key_id = YOUR_ACCESS_KEY
aws_secret_access_key = YOUR_SECRET_KEY
region = us-east-1
```

## License

This project is licensed under the MIT License - see the [LICENSE](./LICENSE) file for details.
