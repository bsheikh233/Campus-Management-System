# Development Guide

## Using Claude Opus in VS Code via GitHub Copilot

This guide explains how to use Claude Opus (Anthropic's most powerful AI model) within Visual Studio Code through GitHub Copilot.

### Prerequisites

1. **GitHub Copilot Subscription**: You need an active GitHub Copilot subscription (Individual, Business, or Enterprise)
2. **VS Code**: Install [Visual Studio Code](https://code.visualstudio.com/)
3. **GitHub Copilot Extension**: Install the GitHub Copilot extension from the VS Code marketplace

### Setup Instructions

#### Step 1: Install Required Extensions

1. Open VS Code
2. Go to Extensions (Ctrl+Shift+X or Cmd+Shift+X on Mac)
3. Search for and install:
   - **GitHub Copilot** (by GitHub)
   - **GitHub Copilot Chat** (by GitHub)

#### Step 2: Sign In to GitHub

1. Click on the GitHub Copilot icon in the status bar (bottom right)
2. Sign in with your GitHub account that has Copilot access
3. Authorize the extensions when prompted

#### Step 3: Enable Claude Opus Model

As of recent updates, GitHub Copilot supports multiple AI models including Claude Opus:

1. Open the Command Palette (Ctrl+Shift+P or Cmd+Shift+P on Mac)
2. Type `GitHub Copilot: Change Model` or `Copilot: Select Model`
3. Select **Claude Opus** from the list of available models

**Alternative Method:**
1. Open GitHub Copilot Chat (Ctrl+Shift+I or click the chat icon)
2. Click on the model selector dropdown at the top of the chat panel
3. Choose **Claude Opus 4** (or the latest Claude Opus version available)

#### Step 4: Configure Model Preferences

You can set Claude Opus as your default model:

1. Go to VS Code Settings (File > Preferences > Settings or Ctrl+,)
2. Search for "GitHub Copilot"
3. Find the "Model" or "Chat Model" setting
4. Select "Claude Opus" from the dropdown

### Using Claude Opus in This Project

#### Chat Mode

1. **Open Copilot Chat**: Press `Ctrl+Shift+I` (or `Cmd+Shift+I` on Mac)
2. Ask questions about the codebase:
   ```
   @workspace How is virtual inheritance implemented in the TA class?
   ```
3. Get help with C++ features:
   ```
   Explain the smart pointer usage in University.h
   ```
4. Request code improvements:
   ```
   How can I improve error handling in the Department class?
   ```

#### Inline Code Suggestions

1. **Start typing** in any C++ file
2. Claude Opus will provide intelligent code completions
3. Press `Tab` to accept suggestions
4. Press `Esc` to dismiss suggestions

#### Useful Commands for This Project

- **Explain code**: Select code and type `/explain` in chat
- **Fix issues**: Select problematic code and type `/fix`
- **Generate tests**: Type `/tests` with context of the function you want to test
- **Refactor code**: Select code and ask "How can I refactor this?"

### Project-Specific Tips

#### Understanding the Codebase

Ask Claude Opus about the architecture:
```
@workspace Explain the relationship between University, Department, and Course classes
```

#### Working with Virtual Inheritance

Get help with the diamond problem:
```
How does the TA class resolve the diamond inheritance problem?
```

#### Adding New Features

Let Claude Opus guide you:
```
I want to add a new Librarian class that inherits from Employee. How should I structure this?
```

#### Debugging

Get debugging assistance:
```
Why might I get a segmentation fault when loading data from university.dat?
```

### Model Comparison

| Feature | Claude Opus | GPT-4 | Claude Sonnet |
|---------|------------|-------|---------------|
| Code Understanding | Excellent | Excellent | Very Good |
| Complex Reasoning | Best | Excellent | Very Good |
| Speed | Moderate | Moderate | Fast |
| Context Window | Large | Large | Large |
| C++ Expertise | Excellent | Excellent | Very Good |

**When to use Claude Opus:**
- Complex architectural decisions
- Deep code analysis
- Comprehensive refactoring
- Understanding intricate inheritance patterns
- Security-critical code reviews

### Troubleshooting

#### Model Not Available
If Claude Opus doesn't appear:
- Ensure your GitHub Copilot subscription includes multi-model support
- Check for VS Code and extension updates
- Sign out and sign back into GitHub Copilot

#### Slow Responses
- Claude Opus is a powerful model and may take slightly longer
- Consider using Claude Sonnet for quick completions
- Switch back to Claude Opus for complex tasks

#### No Suggestions Appearing
1. Check the Copilot icon in the status bar (should show a checkmark)
2. Verify your internet connection
3. Try restarting VS Code
4. Check GitHub Copilot status: https://www.githubstatus.com/

### Best Practices

1. **Be Specific**: Provide context when asking questions
   - Good: "How can I add binary serialization to the Student class?"
   - Less effective: "Help me with serialization"

2. **Use Workspace Context**: Prefix with `@workspace` for codebase-aware answers

3. **Iterate**: If the first response isn't perfect, refine your question

4. **Verify**: Always review and test AI-generated code

5. **Learn**: Use Claude Opus as a learning tool, not just a code generator

### Additional Resources

- [GitHub Copilot Documentation](https://docs.github.com/en/copilot)
- [Claude Model Guide](https://www.anthropic.com/claude)
- [VS Code Copilot Chat Guide](https://code.visualstudio.com/docs/copilot/copilot-chat)

### Building and Testing with AI Assistance

You can ask Claude Opus to help with:
- Writing new Makefile targets
- Adding unit tests (see `test.cpp`)
- Debugging compilation errors
- Optimizing build configurations

Example:
```
Can you help me add a test case for the TA class in test.cpp?
```

---

**Note**: Features and model availability may change. Check the official GitHub Copilot documentation for the latest information.
